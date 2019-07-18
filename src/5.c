#include <stdlib.h>
#include <stdio.h>

//#include <math.h>

// Time

int main(void)
{


float time;

time  = 1.0;
printf("T in seconds		: %.f\n",time);

time = 1e-1;
printf("T in deciseconds	: %.1f\n",time);

time = 1e-2;
printf("T in centiseconds	: %.2f\n",time);

time = 1e-3;
printf("T in milliseconds	: %.3f\n",time);

time = 1e-6;
printf("T in microsecond	: %.6f\n",time);

time = 1e-9;
printf("T in nanoseconds 	: %.9f\n",time);

return EXIT_SUCCESS;

}
