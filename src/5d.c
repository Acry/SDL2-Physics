//BEGIN HEAD

//BEGIN DESCRIPTION

/* DESCRIPTION:
 * Timing precision: Uint64
// SDL_GetPerformanceFrequency
// Use this function to get the count per second of the high resolution counter.
 */

/*
10^-1 s	ds	decisecond 	0.1
10^-2 s	cs	centisecond	0.01
10^-3 s	ms	millisecond	0.001
10^-6 s	µs	microsecond	0.000001
10^-9 s	ns	nanosecond	0.000000001
*/

/* TODO:
 * 
 * 
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
//Some Color Helpers
//R G B
#define RED   		255,0,0,255
#define GREEN 		0,255,0,255
#define BLUE 		0,0,255,255
#define BG		112,170,216,255
//All on
#define WHITE 		255,255,255,255
//All off
#define BLACK 		0,0,0,255
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS

//BEGIN WINDOW AND SCALING
int 		ww;
int 		wh;

//BEGIN VISIBLES
SDL_Color color={BLUE};
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
Uint64 itime		(void);
long double ftime	(void);
void update	(Uint64);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

//BEGIN INIT
(void)argc;
(void)argv;
init();
//BEGIN WINDOW


SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
SDL_SetWindowTitle(Window, "Meassure");
ww=800;
wh=600;
SDL_SetWindowSize(Window, ww,wh);
SDL_ShowWindow(Window);

//END WINDOW

SDL_Event event;
int running 	= 1;
int updates 	= 0;
int updates_acc	= 0;
int pictures 	= 0;
int pictures_acc	= 0;

SDL_SetRenderDrawColor(Renderer, BG);
SDL_RenderClear(Renderer);
//END   INIT

Uint64 currentTime 	= 0;
Uint64 time_acc 	= 0;
Uint64 counter 		= 0;
Uint64 newTime 		= 0;
Uint64 deltaTime 	= 0;
Uint64 frequency	= SDL_GetPerformanceFrequency();
char dt = 0;
SDL_Log("Freq: %lu", frequency);
// exit_();
// return EXIT_SUCCESS;
//BEGIN MAIN LOOP
while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;
				case SDLK_d:	
					dt=dt^1; //XOR - flip var
				default:
					break;
			}
		}
	}


	//BEGIN RENDERING
	pictures++;
	SDL_RenderPresent(Renderer);
	//END   RENDERING

	newTime   		=  itime();
	deltaTime 		=  newTime - currentTime;
	currentTime     	=  newTime;
	time_acc    		+= deltaTime;
	counter			+= deltaTime;
	if (dt)
		update			  (deltaTime);
	updates ++;
	if (counter>frequency){
		SDL_Log("counter: %lu",counter);
		SDL_Log("updates/s: %d",updates);
		SDL_Log("pictures/s: %d",pictures);
		counter = counter - frequency;
		updates_acc += updates;
		updates = 0;
		pictures_acc += pictures;
		pictures = 0;
		
	}
}
//END   MAIN LOOP
Uint64 seconds = time_acc/frequency;
Uint64 rest = time_acc - (seconds*frequency);
SDL_Log("AT:	%lu", time_acc);
SDL_Log("Rest:	%lu", rest);
SDL_Log("AiT:	%lu.%lu", seconds,rest);
SDL_Log("AfT:	%f", (float)time_acc/(float)frequency);
SDL_Log("AU: 	%d", updates_acc);
SDL_Log("AP: 	%d", pictures_acc);
//BEGIN EXIT
exit_();
return EXIT_SUCCESS;
//END 	EXIT

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS

//BEGIN UPDATE
void update(Uint64 dt)
{
	SDL_Log("DT in ns: %lu", dt);
	SDL_Log("DT in ms: %lu", dt/(1000*1000) );
}

Uint64 itime(void)
{
	
	static Uint64 	start = 0;
	if (start==0){
		start	 = SDL_GetPerformanceCounter();
		return 0;
	}
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return counter - start;
}

long double ftime(void)
{
	
	static Uint64 	start = 0;
	static long double 	frequency = 0;
	
	if (start==0){
		start	 = SDL_GetPerformanceCounter();
		frequency= (long double)SDL_GetPerformanceFrequency();
		return 0.0f;
	}
	
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return  (((long double)counter - (long double)start) /frequency);
}
//END 	UPDATE


//END   FUNCTIONS
