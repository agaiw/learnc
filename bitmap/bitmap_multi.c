#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define HSIZE 256

struct bitmap {

  int bmpHeight;
  int bmpWidth;
  int bmpRowSize;
  unsigned char* pixelArray_p;

} bitmap;

struct histogram {

  int blue[HSIZE];
  int green[HSIZE];
  int red[HSIZE];

} histogram;

struct commonParams {

  struct bitmap* bitmap;
  struct histogram* histogram;
  int rowsPerThread;

} commonParams;

struct threadParams {

  struct commonParams* commonParams;
  int startRow;
  int endRow;

} threadParams;

char* loadFile(char* filename);
void readBitmapProperties(char* buffer, struct bitmap* bitmap);
void fillHistogram(struct threadParams* params);
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
  commonParams.rowsPerThread = (bitmap.bmpHeight / numberOfThreads);

  commonParams.histogram = &finalH;
  commonParams.bitmap = &bitmap;

  //threads
  pthread_t* threads = malloc(sizeof(pthread_t) * numberOfThreads);

  struct threadParams* thParams = malloc(sizeof(struct threadParams) * numberOfThreads);

  for (int i = 0; i < numberOfThreads; i++) {

    struct threadParams* params = (thParams + i);
//    struct threadParams params;
    params->commonParams = &commonParams;
    params->startRow = i * (params->commonParams)->rowsPerThread;
    params->endRow = ((params->startRow + (params->commonParams)->rowsPerThread) > bitmap.bmpHeight ? (bitmap.bmpHeight + 1) : params->startRow + (params->commonParams)->rowsPerThread);
    pthread_create((threads + i), NULL, fillHistogram, params);

  }

  for (int i = 0; i < numberOfThreads; i++) {

  pthread_join(threads[i], NULL);

  }
  free(thParams);
  free(threads);
  free(buffer);

  for (int i = 0; i < HSIZE; i++) {

    printf("%d\t%d\t%d\t%d\t\n", i, finalH.blue[i], finalH.green[i], finalH.red[i]);

  }
  return 0;

}
void fillHistogram(struct threadParams* params) {

  struct histogram tempH;

  for (int i = 0; i < HSIZE; i++) {

    tempH.blue[i] = 0;
    tempH.green[i] = 0;
    tempH.red[i] = 0;
  }

  int offset = (((params->commonParams)->bitmap)->bmpRowSize) * (params->startRow);
  unsigned char* tempArray_p = ((params->commonParams)->bitmap)->pixelArray_p + offset;

  for (int i = params->startRow; i < params->endRow; i++) {

    unsigned char* tempRow_p = tempArray_p;

    for (int j = 0; j < ((params->commonParams)->bitmap)->bmpWidth; j++) {

      tempH.blue[*(tempRow_p)] += 1;
      tempH.green[*(tempRow_p + 1)] += 1;
      tempH.red[*(tempRow_p + 2)] += 1;
      tempRow_p += 3;

      }

    tempArray_p += ((params->commonParams)->bitmap)->bmpRowSize;
  }

  pthread_mutex_lock(&histogramLock);

  for (int i = 0; i < HSIZE; i++) {

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
