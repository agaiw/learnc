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

  int offset;
  int* hArray;
  struct bitmap* bitmap;

} histogram;

char* loadFile(char* filename);
void readBitmapProperties(char* buffer, struct bitmap* bitmap);
void fillHistogram(struct histogram* histogram);

int main(int argc, char* argv[]) {

  char* buffer = loadFile(argv[1]);
  readBitmapProperties(buffer, &bitmap);
  
  int hRed[256];
  int hGreen[256];
  int hBlue[256]; 

  struct histogram histogramB = {2, hBlue, &bitmap};
  struct histogram histogramG = {1, hGreen, &bitmap};
  struct histogram histogramR = {0, hRed, &bitmap};

  //threads
  pthread_t threadR;
  pthread_t threadG;
  pthread_t threadB;

  pthread_create(&threadB, NULL, fillHistogram, &histogramB);
  pthread_create(&threadG, NULL, fillHistogram, &histogramG);
  pthread_create(&threadR, NULL, fillHistogram, &histogramR);

  pthread_join(threadB, NULL);
  pthread_join(threadG, NULL);
  pthread_join(threadR, NULL);

  free(buffer);

  for (int i = 0; i < 256; i++) {

    printf("%d\t%d\t%d\t%d\t\n", i, hBlue[i], hGreen[i], hRed[i]);

  }

  return 0;

}
void fillHistogram(struct histogram* histogram) {

  for (int i = 0; i < 256; i++) {

    *(histogram->hArray + i) = 0;

  }
  unsigned char* tempArray_p = (histogram->bitmap)->pixelArray_p;

  for (int i = 0; i < (histogram->bitmap)->bmpHeight; i++) {

    unsigned char* tempRow_p = tempArray_p;

    for (int j = 0; j < (histogram->bitmap)->bmpWidth; j++) {

      histogram->hArray[*(tempRow_p + histogram->offset)] += 1;
      tempRow_p += 3;

      }

    tempArray_p += (histogram->bitmap)->bmpRowSize;

  }
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
