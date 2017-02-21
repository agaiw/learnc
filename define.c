#include <stdio.h>



#define SIZE(arr) ((sizeof(arr)) / (sizeof(arr[0])))

void main() {

int arr[] = {1,2,3,6,8};

printf("Size: %zu\n", SIZE(arr));


}
