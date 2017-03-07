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

  for (int i = 0; i < 256; i++) {

  finalH.blue[i] = 0;
  finalH.green[i] = 0;
  finalH.red[i] = 0;

  }

  if (argc < 3) {

    printf("Error\n");
    return -1;

  }

  char* buffer = loadFile(argv[1]);
  int numberOfThreads = atoi(argv[2]);

  readBitmapProperties(buffer, &bitmap);
  printf("array address: %p\n", bitmap.pixelArray_p);
  commonParams.rowsPerThread = (bitmap.bmpHeight / numberOfThreads);

  commonParams.histogram = &finalH;
  commonParams.bitmap = &bitmap;

  printf("rows per thread: %d\n", commonParams.rowsPerThread);

  //threads
  pthread_t* threads = malloc(sizeof(pthread_t) * numberOfThreads);

  printf("numberofthreads: %d\n", numberOfThreads);

  for (int i = 0; i < numberOfThreads; i++) {

    struct threadParams params;
    params.commonParams = &commonParams;
    params.startRow = i * (params.commonParams)->rowsPerThread;
    params.endRow = ((params.startRow + (params.commonParams)->rowsPerThread) > bitmap.bmpHeight ? (bitmap.bmpHeight + 1) : params.startRow + (params.commonParams)->rowsPerThread);
    printf("start row: %d, end row: %d\n", params.startRow, params.endRow);

    pthread_create((threads + i), NULL, fillHistogram, &params);

  }

  for (int i = 0; i < numberOfThreads; i++) {

  pthread_join(threads[i], NULL);

  }

  free(buffer);

  int B = 0;
  int G = 0;
  int R = 0;

  for (int i = 0; i < 256; i++) {

    printf("%d\t%d\t%d\t%d\t\n", i, finalH.blue[i], finalH.green[i], finalH.red[i]);
    B += finalH.blue[i];
    G += finalH.green[i];
    R += finalH.red[i];

  }
  printf("B: %d, G: %d, R: %d\n", B, G, R);
  return 0;

}
void fillHistogram(struct threadParams* params) {

  int sumBlue = 0;
  int sumGreen = 0;
  int sumRed = 0;
  int sumBlueFinal = 0; 
  int sumGreenFinal = 0; 
  int sumRedFinal = 0; 
  struct histogram tempH;

  for (int i = 0; i < 256; i++) {

    tempH.blue[i] = 0;
    tempH.green[i] = 0;
    tempH.red[i] = 0;
  }

  int offset = (((params->commonParams)->bitmap)->bmpRowSize) * (params->startRow);
  unsigned char* tempArray_p = ((params->commonParams)->bitmap)->pixelArray_p + offset;
  printf("startRow: %d, offset: %d, tempArray_p: %p\n", params->startRow, offset, tempArray_p);

  for (int i = params->startRow; i < params->endRow; i++) {


    unsigned char* tempRow_p = tempArray_p + offset;

    for (int j = 0; j < ((params->commonParams)->bitmap)->bmpWidth; j++) {

      tempH.blue[*(tempRow_p)] += 1;
      tempH.green[*(tempRow_p + 1)] += 1;
      tempH.red[*(tempRow_p + 2)] += 1;
      tempRow_p += 3;

      }

    tempArray_p += ((params->commonParams)->bitmap)->bmpRowSize;
  }

  pthread_mutex_lock(&histogramLock);

  for (int i = 0; i < 256; i++) {

    finalH.blue[i] += tempH.blue[i];
    finalH.green[i] += tempH.green[i];
    finalH.red[i] += tempH.red[i];
    
   sumBlue += tempH.blue[i];
   sumGreen += tempH.green[i];
   sumRed += tempH.red[i];

  sumBlueFinal += finalH.blue[i];
  sumGreenFinal += finalH.green[i];
  sumRedFinal += finalH.red[i];
  }
  printf("in this thread sumBlue: %d, sumGreen: %d, sumRed: %d\n", sumBlue, sumGreen, sumRed);
  printf("in this thread sumBlueFinal: %d, sumGreenFinal: %d, sumRedFinal: %d\n", sumBlueFinal, sumGreenFinal, sumRedFinal);
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
