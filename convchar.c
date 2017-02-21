#include <stdio.h>

int string2int(const char* string);


void main() {

char* string = "-147";
char* string2 = "345";

printf("Liczba %s: %d\n", string, string2int(string));

printf("Liczba %s: %d\n", string2, string2int(string2));


}


int string2int(const char* string) {

  char* currChar = string;

  int num = 0;

  int sign = 1;

  int digit;

    if (currChar == string && *currChar == '-') { 
  
      sign = -1; 
    }

  while (*currChar != '\0') {

    if(*currChar >= '0' && *currChar <= '9') {

      digit = *currChar - '0';

      num = num * 10 + digit;

    }
    currChar = currChar + 1;
  }
    return sign * num;


}
