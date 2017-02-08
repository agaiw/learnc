#include <stdio.h>

char memory[1000];

short** allocateArr(int row, int col, char memory[]);
void fillArr(int row, int col, short** arr);
void printArr(int row, int col, short** arr);

void main() {

  short** arr1 = allocateArr(10, 10, memory);
  short** arr2 = allocateArr(5, 8, memory);
  fillArr(10, 10, arr1);
  fillArr(5, 8, arr2);
  printArr(10, 10, arr1);
  printArr(5, 8, arr2);

}

short** allocateArr(int row, int col, char memory[]) { 

  static int firstfree = 0;

  int size = sizeof(short) * row * col + sizeof(short*) * row;

  short** arr = (short**)memory + firstfree;

  for (int k = 0; k < row; k++) {
 
    *(arr + k) = (char*)arr + row * sizeof(short*) + k * col * sizeof(short);
  } 

  firstfree += size;
  
  return (short**)arr; 
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

