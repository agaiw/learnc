#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

  struct parameters {
    int bitmapHeight;
    int bitmapWidth;
    int rowSize;
    unsigned char* pixelArray_p;
    int offset;
    int* hArray;

  } parameters;

void fillHistogram(struct parameters* parameters);

int main() {

  FILE* pFile;
  long lSize;
  char* buffer;
  size_t result;

  pFile = fopen("sample.bmp", "rb");
  
  fseek(pFile, 0, SEEK_END);
  lSize = ftell(pFile); 
  fseek(pFile, 0, SEEK_SET); 

  buffer = (char*)malloc(sizeof(char) * lSize);

  result = fread(buffer, 1, lSize, pFile);
  fclose(pFile);

  int pixelArrayOffset = *((int*)(buffer + 10));
 
  unsigned char* pixelArray_p = buffer + 54;

  int bitmapWidth = *((int*)(buffer + 18));
  int bitmapHeight = *((int*)(buffer + 22));

  short bitsPerPixel = *((short*)(buffer + 28)); //24

  int rowSize = ((int)((bitsPerPixel * bitmapWidth + 31) / 32)) * 4;

  int hRed[256];
  int hGreen[256];
  int hBlue[256]; 

  struct parameters parametersB = {bitmapHeight, bitmapWidth, rowSize, pixelArray_p, 2, hBlue};
  struct parameters parametersG = {bitmapHeight, bitmapWidth, rowSize, pixelArray_p, 2, hGreen};
  struct parameters parametersR = {bitmapHeight, bitmapWidth, rowSize, pixelArray_p, 2, hRed};

  //threads
  pthread_t threadR, threadG, threadB;

  pthread_create(&threadB, NULL, &fillHistogram, &parametersB);
  pthread_create(&threadG, NULL, &fillHistogram, &parametersG);
  pthread_create(&threadR, NULL, &fillHistogram, &parametersR);

  pthread_join(threadB, NULL);
  pthread_join(threadG, NULL);
  pthread_join(threadR, NULL);

  free(buffer);

 
  for(int i = 0; i < 256; i++) {
    printf("%d\t%d\t%d\t%d\n", i, hBlue[i], hGreen[i], hRed[i]); 
  }

  return 0;

}
void fillHistogram(struct parameters* parameters) {

  for (int i = 0; i < 256; i++) {

    *(parameters->hArray + i) = 0;

  }

  unsigned char* tempArray_p = parameters->pixelArray_p;

  for (int i = 0; i < parameters->bitmapHeight; i++) {

    unsigned char* tempRow_p = tempArray_p;

    for (int j = 0; j < parameters->bitmapWidth; j++) {

      parameters->hArray[*(tempRow_p + parameters->offset)] += 1;
      tempRow_p += 3;

    }

    tempArray_p += parameters->rowSize;

  return;

}








}


