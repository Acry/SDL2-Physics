#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(void)
{

float distance 	= 38.06;		// metres
float gravity	=  9.81;	// metres/seconds²

float time	= sqrtf(2 * distance / gravity);

printf("Gravity is a defined constant, g = -9.8 m/s²\n");
printf("Given the distance of %.2f m's the falling time is: %.2f seconds.\n", distance ,time);

// You're standing at the edge of a cliff and drop a ball. It takes 10 sec to hit the ground. 

time = 10.0;

// How high up are you?
// h = 1/2 gt²
// 1/2 (9.8 m/s²) * (10 sec)²
// h = 490 m
distance = gravity * powf(time,2) * 0.5;
printf("Given the time of %.2f seconds the distance is: %.2f metres.\n",time, distance);

// What was the velocity of the ball?
// v = gt
// v = 9.8 m/s² * 10 seconds.
// v = 98 m/s
float velocity;
velocity = gravity * time;
printf("Given the time of %.2f seconds the velocity is: %.2f metres/second.\n",time, velocity);

// 1 Kilometer sind 1000 Meter.
// 1 Stunde sind 3600 Sekunden.
float km_h = velocity/1000*3600;

printf("That are %.2f kilometres per hour.\n",km_h);
km_h = velocity*3.6;
printf("That are %.2f kilometres per hour.\n",km_h);

float acceleration;
// a = v/t
acceleration = velocity / time;
printf("Acc: %.2f .\n",acceleration);
return EXIT_SUCCESS;

}
