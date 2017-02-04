#include <stdio.h>

void allocateArr(int row, int col, short*** arr);
void fillArr(int row, int col, short** arr);
void printArr(int row, int col, short** arr);
void freeArr(int row, short** arr);

void main() {

  int row = 10;
  int col = 10;
  short** arr;

  allocateArr(row, col, &arr);
  fillArr(row, col, arr);
  printArr(row, col, arr);
  freeArr(row, arr);

}

void allocateArr(int row, int col, short*** arr) { 

  *arr = (short**)malloc(sizeof(short*) * row);

  for (int i = 0; i < row; i++) {

    (*arr)[i] = (short*)malloc(sizeof(short) * col);

  }
}

void fillArr(int row, int col, short** arr) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      arr[i][j] = i * j;

    }
  }
}


void printArr(int row, int col, short** arr) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      printf("%03d ", arr[i][j]);

     }
      printf("\n");
  }
}

void freeArr(int row, short** arr) {
  for(int i = 0; i < row; i++) {
    
  free(arr[i]);

  }

  free(arr);
}
