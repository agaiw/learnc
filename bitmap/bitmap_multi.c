#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct bitmap {

  int bmpHeight;
  int bmpWidth;
  int bmpRowSize;
  unsigned char* pixelArray_p;

} bitmap;

struct histogram {

  int blue[256];
  int green[256];
  int red[256];

} histogram;

struct fParameters {

  struct bitmap* bitmap;
  struct histogram* histogram;
  int startRow;
  int endRow;

} fParameters;

char* loadFile(char* filename);
void readBitmapProperties(char* buffer, struct bitmap* bitmap);
void fillHistogram(struct fParameters* fParameters);
pthread_mutex_t histogramLock;
struct histogram finalH;

int main(int argc, char* argv[]) {

  if (argc < 3) {

    printf("Error\n");
    return -1;

  }

  char* buffer = loadFile(argv[1]);
  int numberOfThreads = atoi(argv[2]);

  readBitmapProperties(buffer, &bitmap);

  int rowsPerThread = (bitmap.bmpHeight / numberOfThreads) + 1;

  fParameters.histogram = &finalH;
  fParameters.bitmap = &bitmap;
  fParameters.startRow = 0;
  fParameters.endRow = 0;
  fParameters.endRow = fParameters.startRow + rowsPerThread;

  printf("rows per thread: %d\n", rowsPerThread);

  //threads
  pthread_t* threads = malloc(sizeof(pthread_t) * numberOfThreads);

  for (int i = 0; i < numberOfThreads; i++) {

  fParameters.startRow = i * rowsPerThread;
  fParameters.endRow = ((fParameters.startRow + rowsPerThread) > bitmap.bmpHeight ? bitmap.bmpHeight : fParameters.startRow + rowsPerThread);
  printf("start row: %d, end row: %d\n", fParameters.startRow, fParameters.endRow);

  pthread_t thread;
  *(threads + i) = &thread;
  pthread_create(&thread, NULL, fillHistogram, &fParameters);

  }

  for (int i = 0; i < numberOfThreads; i++) {

  pthread_join(threads[i], NULL);

  }

  free(buffer);

  for (int i = 0; i < 256; i++) {

    printf("%d\t%d\t%d\t%d\t\n", i, finalH.blue[i], finalH.green[i], finalH.red[i]);

  }

  return 0;

}
void fillHistogram(struct fParameters* fParameters) {

  struct histogram tempH;

  for (int i = 0; i < 256; i++) {

    tempH.blue[i] = 0;
    tempH.green[i] = 0;
    tempH.red[i] = 0;
  }

  unsigned char* tempArray_p = (fParameters->bitmap)->pixelArray_p;

  for (int i = fParameters->startRow; i < fParameters->endRow; i++) {

    unsigned char* tempRow_p = tempArray_p;

    for (int j = 0; j < (fParameters->bitmap)->bmpWidth; j++) {

      tempH.blue[*(tempRow_p)] += 1;
      tempH.green[*(tempRow_p) + 1] += 1;
      tempH.red[*(tempRow_p) + 2] += 1;
      tempRow_p += 3;

      }

    tempArray_p += (fParameters->bitmap)->bmpRowSize;

  }

  pthread_mutex_lock(&histogramLock);

  for (int i = 0; i < 256; i++) {

    finalH.blue[i] += tempH.blue[i];
    finalH.green[i] += tempH.green[i];
    finalH.red[i] += tempH.red[i];
  }
 
  pthread_mutex_unlock(&histogramLock);
  
  return;
}

char* loadFile(char* filename) {

  FILE* pFile;
  long lSize;
  char* buffer;
  size_t result;

  pFile = fopen(filename, "rb");
  
  fseek(pFile, 0, SEEK_END);
  lSize = ftell(pFile); 
  fseek(pFile, 0, SEEK_SET); 

  buffer = (char*)malloc(sizeof(char) * lSize);

  result = fread(buffer, 1, lSize, pFile);
  fclose(pFile);

  return buffer;

}

void readBitmapProperties(char* buffer, struct bitmap* bitmap) {

  bitmap->pixelArray_p = buffer + 54;
  bitmap->bmpWidth = *((int*)(buffer + 18));
  bitmap->bmpHeight = *((int*)(buffer + 22));
  short bitsPerPixel = *((short*)(buffer + 28));
  bitmap->bmpRowSize = ((int)((bitsPerPixel * bitmap->bmpWidth + 31) / 32)) * 4;

}
