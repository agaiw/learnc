#include <stdio.h>

void main() {

  int row = 10;
  int col = 10;

  short** arr = (short**)malloc(sizeof(short*) * row);

  for (int i = 0; i < row; i++) {

    arr[i] = (short*)malloc(sizeof(short) * col);

  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      arr[i][j] = i * j;

    }
  }


  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {

      printf("%03d ", arr[i][j]);

     }
      printf("\n");
  }


  for(int i = 0; i < row; i++) {
    
  free(arr[i]);

  }

  free(arr);


}
