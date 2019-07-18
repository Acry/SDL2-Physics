//BEGIN HEAD
//BEGIN DESCRIPTION

/* Window Size in SI-Units
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
//Some Color Helpers
//R G B
#define RED   	255,0,0,255
#define GREEN 	0,255,0,255
#define BLUE 	0,0,255,255
//All on
#define WHITE 	255,255,255,255
//All off
#define BLACK 	0,0,0,255


//Real Size in SI-Unit centimeters
#define REALSIZE_H 	13.0
#define REALSIZE_V 	 9.0

//temporarily Window Size
#define WW 		100	
#define WH 		100


#define CENTI_PER_INCH 2.54
//10 pixel == 1 m
//0,277778 Meter pro Sekunde == 1km/h
//
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
struct scalar2{
	float x;
	float y;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;

struct scalar2 dpi;
float 	boxLocation;   		//  horizontal location of box
float 	boxVelocity;   		//  horizontal velocity of box
float 	boxWidth;         	//  width of box in pixels.

float 	time;      		//  elapsed time.
float 	timeIncrement;

SDL_Rect 	box;
SDL_Rect 	box2;
//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;
SDL_Texture    *gepard		= NULL;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
float time_(void);
void query_disp (void);
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
//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "Window in centimetres");
SDL_ShowWindow(Window);
//END WINDOW
query_disp();
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
assets_in();
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
		boxLocation+= boxVelocity*deltaTime;
		box.x=roundf(boxLocation);
	}
	//END LOGIC

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, BLUE);
	SDL_RenderFillRect(Renderer, &box);
	SDL_SetRenderDrawColor(Renderer, RED);
	SDL_RenderFillRect(Renderer, &box2);
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

	boxLocation 	= 0.0;
	box.x		= roundf(boxLocation);

	boxVelocity 	= 200; //dezimeter pro sekunde oder 20m p/s o. 72 km/h
	boxWidth 	= 15;
	box.w		= roundf(boxWidth);
	float he 	= (float)h/((float)w/15);
	box.h		= roundf(he);
	box.y		= wh-box.h;
	
	//giving Box size in Centimeters
	box2.w		= roundf(2.0/CENTI_PER_INCH*dpi.x);
	box2.h		= roundf(2.0/CENTI_PER_INCH*dpi.y);
	
	box2.x		= ww/2-box2.w/2;
	box2.y		= wh/2-box2.h/2;
}

void assets_out(void)
{
	SDL_DestroyTexture(gepard);
}
void query_disp	(void)
{
	int disp;
	
	disp=SDL_GetWindowDisplayIndex(Window);
	SDL_GetDisplayDPI(disp, NULL,&dpi.x, &dpi.y);
	
	SDL_Log("hdpi: %f", dpi.x);
	ww=roundf(SCALE_SIZE_H/CENTI_PER_INCH*dpi.x);

	SDL_Log("vdpi: %f", dpi.y);
	wh=roundf(REALSIZE_V/CENTI_PER_INCH*dpi.y);
	SDL_Log("w: %d, h: %d",ww,wh);
	SDL_SetWindowSize(Window, ww,wh);
	
}
//END   FUNCTIONS
