
char* description = "Program that demonstrates extracting bits from 32-bit (single) floating point number.";

#include <stdio.h>

typedef char BYTE;

union FloatBits{
  float f;
  struct {
    BYTE mnt3:8;
    BYTE mnt2:8;
    BYTE mnt1:7;
    BYTE exp2:1;
    BYTE exp1:7;
    BYTE sign:1;
  } bits;
};


void ftobits(float f, int *sign, int *exp, long *man) {
  union FloatBits fb;
  fb.f = f;
  *sign = fb.bits.sign;
  *exp = fb.bits.exp2 + fb.bits.exp1*2;
  if (*exp != 0) {
    *exp -= 127;
  }
  *man = (fb.bits.mnt1<<16) + (fb.bits.mnt2<<8) + fb.bits.mnt3;
}

int main(char** argv) {
  printf("%s\n", description);

  float numbers[6] =  { -1024.125, 1.1, 0, 1.40129846432e-45, 0.5, 3.40282346639e38 };
  for (int i=0; i<6; i++) {
  float a = numbers[i];
  int sign;
  int exp;
  long man;

  printf("\nfloat        = %.9f\n", a);
  ftobits(a, &sign, &exp, &man);
  printf("printf(%%a)   = %a\n", a);
  printf("sign         = %d\n", sign);
  printf("exponent     = %d\n", exp);
  printf("mantissa     = 0x%x\n", man*2);
  printf("mantissa     = %d\n", man);
  }
  return 0;
}

