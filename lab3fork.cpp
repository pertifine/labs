#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <float.h>

int count;
int call = 0;

float fun(float Ud)
{
	float E = 15, R = 3E3, i0 = 8E-9, m = 1.6, Fit = 26E-3;
	float id;

	float expa = (Ud / m / Fit);
	count++;
	if (expa > 69)
	{
		id = i0 * 1e30;
	}
	else 
	{
		id = i0 * (expf(expa) - 1);
	}
	++call;
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
	float FC, FCB;
	int i = 0;

	do
		
	{
		i++;
		FC = f(a);
		FCB = (f(a + eps) - FC) / eps;
		a = a - FC / FCB;
		
		printf("#%d a = %f f(x) = %f \n", i, a, FC);
	} while (fabs(FC / FCB) > eps * fabs(a));
	
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
	call = 0;

	count = 0;
	printf("Metod bisekcii:\n");
	x = bis(fun, 0, 6, eps);
	printf("%d number of call funtion\n", call);
	printf("Ansvwer is %f\nfun used:%d\n\n", x, count);
	

	count = 0;
	printf("Metod Nutona:\n");
	x = nuton(fun, 1, eps);
	printf("%d number of call funtion\n", call);
	printf("Ansvwer is %f\nfun used:%d\n\n", x, count);
	
	
	count = 0;
	printf("Metod Sichnux:\n");
	x = sichni(fun, 1, eps);
	printf("Ansvwer is %f\nfun used:%d\n", x, count);
	printf("%d number of call funtion\n", call);

	system("pause");
	return 0;
}
