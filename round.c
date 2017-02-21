#include <stdio.h>

long round(float val);


void main() {




  printf("12.3: %d\n", round(12.3));

  printf("-2.2: %d\n", round(-2.2));

  printf("1.5: %d\n", round(1.5));
  printf("1.4: %d\n", round(1.4));
  printf("1.7: %d\n", round(1.7));
  printf("-1.2: %d\n", round(-1.2));
  printf("-1.5: %d\n", round(-1.5));
} 


long round(float val) {


  long  val_floored = (int)val;
  float diff = val - val_floored;
  long result = (diff < 0.5) ? val_floored : ((val > 0) ? (val_floored + 1) : (val_floored - 1)); 

  return result;
}
