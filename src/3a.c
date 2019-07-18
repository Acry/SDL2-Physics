#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

float distance 	= 50;
float gravity	= 9.81;
float time	= sqrtf(2 * distance / gravity);
printf("t: %f\n",time);
return EXIT_SUCCESS;

}
