Eldar Alekperov:
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <float.h>

int count;

float fun(float Ud)
{
 float E = 5, R = 1E3, i0 = 3E-9, m = 1.7, Fit = 26E-3;
 float id;

 count++;

 id = i0* (expf ( Ud / m * Fit) - 1);
 return E - Ud - R * id;
}

float bis(float f(float), float a, float b, float eps)
{
 int i = 0;
 float fa, x, fx;
 fa = f(a);
 fa /= fabsf(fa);
 do
 {
  i++;
  x = (a + b) / 2;
  fx = f(x);
  if (fa * fx < 0)
  {
   b = x;
  }
  else
   a = x;
  printf("#%d a = %f b = %f f(x) = %f \n", i, a, b, fx);
 } while (fabs(b - a) > eps * fabs(a));
 return (a + b) / 2;
}

float nuton(float f(float), float a, float eps)
{
 float FC, FCB ;
 int i = 0;
 do
 {
  i++;
  FC = f(a);
  FCB = (f(a + eps) - FC) / eps;
  a = a - FC / FCB;
  printf("#%d a = %f f(x) = %f \n", i, a, FC);
 } while (fabs(FC) > eps);
 return a;
}


float sichni(float f(float), float a, float eps)
{
 float FC, FCB, k, q1, q2;
 int i = 1;
 FC = f(a);
 k = fabsf(a) * sqrtf(FLT_EPSILON);
 FCB = (f(a + k) - FC) / k;
 q1 = a - FC / FCB;
 printf("#%d a = %f f(x) = %f \n", i, a, FC);
 do
 {
  i++;
  q2 = q1;
  FCB = f(q1);
  q1 = q1 - (q1 - a) * FCB / (FCB - FC);
  a = q2;
  FC = FCB;
  printf("#%d a = %f f(x) = %f \n", i, a, FC);
 } while (fabs(q1 - a) > eps * fabs(a));
 return a;
}

int main(void)
{
 float x = 0, eps = 10E-6;

 count = 0;
 printf("Metod bisekcii:\n");
 x = bis(fun, 0, 6, eps);
 printf("Ansvwer is %f\nfun used:%d\n\n", x, count);

 count = 0;
 printf("Metod Nutona:\n");
 x = nuton(fun, 1, eps);
 printf("Ansvwer is %f\nfun used:%d\n\n", x, count);

 count = 0;
 printf("Metod Sichnux:\n");
 x = sichni(fun, 1, eps);
 printf("Ansvwer is %f\nfun used:%d\n", x, count);
 system("pause");
 return 0;
}
