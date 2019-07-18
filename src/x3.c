//BEGIN HEAD
//BEGIN DESCRIPTION

/* Acceleration
 *
 */

/* DEFINED PROGRESS GOALS
 * 
 * None atm
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
#define WHITE 	255,255,255,255
#define BLACK 	0,0,0,255
#define BLUE 	0,0,255,255
#define RED   	255,0,0,255
#define WW 	1000 // dezimeter = 100m
#define WH 	100 // dezimeter  = 10m
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;
float 	boxLocation;   		//  horizontal location of box
float 	boxVelocity;   		//  horizontal velocity of box
float 	acceleration;
float 	boxWidth;         	//  width of box in pixels.

float 	time;      		//  elapsed time.
float 	timeIncrement;

SDL_Rect 	box;

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;
SDL_Texture    *gepard		= NULL;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
float time_(void);
void assets_in	(void);
void assets_out	(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "SDL2 Template");
SDL_ShowWindow(Window);
//END WINDOW

SDL_Event event;
int running = 1;
float currentTime = 0.0f;
float accumulator = 0.0f;

//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				;
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){
				boxLocation=0;
				box.x=roundf(boxLocation);
			}
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP

	//BEGIN LOGIC
	float newTime = time_();
	float deltaTime = newTime - currentTime;
	currentTime = newTime;
	accumulator += deltaTime;
	if (box.x < ww) {
		boxVelocity+=
		boxLocation+= boxVelocity*deltaTime;
		box.x=roundf(boxLocation);
	}
	//END LOGIC

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, BLUE);
	SDL_RenderFillRect(Renderer, &box);
	SDL_RenderCopy(Renderer, gepard, NULL, &box);
	SDL_RenderPresent(Renderer);
	//END   RENDERING
	
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
float time_(void)
{
	
	static Uint64 start = 0;
	static float frequency = 0;
	
	if (start==0){
		start	 = SDL_GetPerformanceCounter();
		frequency= (float)SDL_GetPerformanceFrequency();
		return 0.0f;
	}
	
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return  (((float)counter - (float)start) /frequency);
// 	real64 MSPerFrame = (((1000.0f * (real64)CounterElapsed) / (real64)PerCountFrequency));
}

void assets_in(void)
{

	int w,h;

	temp_surface = IMG_Load("./assets/gfx/gepard.png");
	gepard = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(gepard, NULL, NULL, &w, &h);
	SDL_Log("w: %d, h: %d",w,h);

	boxLocation 	= 0.0;
	box.x		= roundf(boxLocation);

	boxVelocity 	= 0; //dezimeter pro sekunde oder 20m p/s o. 72 km/h
	boxWidth 	= 15;
	box.w		= roundf(boxWidth);
	float he 	= (float)h/((float)w/15);
	box.h		= roundf(he);
	box.y		= WH-box.h;
}

void assets_out(void)
{
	SDL_DestroyTexture(gepard);
}

//END   FUNCTIONS
