#include <stdio.h>

struct test {

  char a;
  short b;
  char c;
  char d;
  int e;
  long long f;

};

void main() {

  struct test str;

  printf("Offset of a: %d\n", ((int)&str.a - (int)&str));
  printf("Offset of b: %d\n", ((int)&str.b - (int)&str));
  printf("Offset of c: %d\n", ((int)&str.c - (int)&str));
  printf("Offset of d: %d\n", ((int)&str.d - (int)&str));
  printf("Offset of e: %d\n", ((int)&str.e - (int)&str));
  printf("Offset of f: %d\n", ((int)&str.f - (int)&str));



}
