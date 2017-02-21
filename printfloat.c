#include <stdio.h>

void main() {

float num = 3.445677f;
int* num_p = (int*)&num;
int num_int = *((int*)(num_p));

printf("Float num %f represented as hex: %x\n\n", num, num_int);

double num2 = 3.445677;
long long* num2_p = &num2;
long long num2_int = *((long long*)(num2_p));
printf("Double num2 %f represented as hex: %llx\n\n", num2, num2_int);

}
