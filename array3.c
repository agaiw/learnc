#include <stdio.h>

void allocateArr(int row, int col, short*** arr);
void fillArr(int row, int col, short** arr);
void printArr(int row, int col, short** arr);
void freeArr(int row, short** arr);

void main() {

  int row = 2;
  int col = 3;
  short** arr;

  allocateArr(row, col, &arr);
  fillArr(row, col, arr);
  printArr(row, col, arr);
  freeArr(row, arr);

}

void allocateArr(int row, int col, short*** arr) { 

  *arr = (short**)malloc(sizeof(short) * row * col + sizeof(short*) * row);
  printf("   %p - %d x %d = %zu\n", *arr, row, col, row * sizeof(short*));
  for (int k = 0; k < row; k++) {
 
    (*arr)[k] = (char*)*arr + row * sizeof(short*) + k * col * sizeof(short);
    printf("%u: %p\n", k, (*arr)[k]);
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

  free(arr);
}
