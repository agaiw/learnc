#include <stdio.h>

char memory[1000];

char** allocateArr(int row, int col, char memory[], size_t size);
void fillArrShort(int row, int col, short** arr);
void printArrShort(int row, int col, short** arr);
void fillArrInt(int row, int col, int** arr);
void printArrInt(int row, int col, int** arr);

void main() {

  short** arr1 = (short**)allocateArr(10, 2, memory, sizeof(short));
  int** arr2 = (int**)allocateArr(5, 7, memory, sizeof(int));
  fillArrShort(10, 2, arr1);
  fillArrInt(5, 7, arr2);
  printArrShort(10, 2, arr1);
  printArrInt(5, 7, arr2);

}

char** allocateArr(int row, int col, char memory[], size_t size) { 

  static int firstfree = 0;

  int arrsize = size * row * col + sizeof(void*) * row;

  void** arr = (void**)memory + firstfree;

  for (int k = 0; k < row; k++) {
 
    *(arr + k) = (char*)arr + row * sizeof(void*) + k * col * size;

  } 

  firstfree += arrsize;
  
  return (char**)arr; 
}

void fillArrShort(int row, int col, short** arr) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      arr[i][j] = i * j;
    }
  }
}


void printArrShort(int row, int col, short** arr) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      printf("%03d ", arr[i][j]);

     }
      printf("\n");
  }
}

void fillArrInt(int row, int col, int** arr) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      arr[i][j] = i * j;

    }
  }
}


void printArrInt(int row, int col, int** arr) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      printf("%03d ", arr[i][j]);

     }
      printf("\n");
  }
}


