#include <stdio.h>
#include <stdlib.h>


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

  for (int i = 0; i < 256; i++) {

    hRed[i] = 0;
    hGreen[i] = 0;
    hBlue[i] = 0;
  }

  unsigned char* tempArray_p = pixelArray_p;

  for (int i = 0; i < bitmapHeight; i++) {

    unsigned char* tempRow_p = tempArray_p;

    for (int j = 0; j < bitmapWidth; j++) {

      hRed[*(tempRow_p)] += 1;
      hGreen[*(tempRow_p + 1)] += 1;
      hBlue[*(tempRow_p + 2)] += 1;
      tempRow_p += 3;

    }

    tempArray_p += rowSize;

  }


  free(buffer);

  return 0;

}
