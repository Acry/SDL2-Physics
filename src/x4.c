//BEGIN HEAD
//BEGIN DESCRIPTION

/* This is a light SDL2 template
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
#define WW 	550
#define WH 	(WW/16)*12
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;
float 	boxLocation;   		//  horizontal location of box
float 	boxVelocity;   		//  horizontal velocity of box
int 	boxWidth;         	// width of box in pixels.
float 	initialAltitude;
float 	ballAltitude;  		//  vertical location of ball
float 	ballLocation;  		//  horizontal location of ball
float 	ball_mass = 0.1;
float 	g;         		//  gravitational acceleration
float 	time;      		//  elapsed time.
float 	timeIncrement;

SDL_Rect 	box;
SDL_Rect 	ball;

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;
//END 	VISIBLES

SDL_Point	mouse;

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
				;
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
	if (ballAltitude < WH) {
		time += time_(); 
		boxLocation = boxVelocity*time;
		box.x=roundf(boxLocation);
		
		ballAltitude = initialAltitude + ball_mass * g * time * time;
		ball.y= roundf(ballAltitude);
		SDL_Log("ball.y: %d", ball.y);
		SDL_Log("time=%lf  boxLocation=%lf  ballAltitude=%lf\n",
		       time, boxLocation, ballAltitude);
	}
	//END LOGIC

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, BLUE);
	SDL_RenderFillRect(Renderer, &box);
	SDL_SetRenderDrawColor(Renderer, RED);
	SDL_RenderFillRect(Renderer, &ball);
	SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);

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
	static Uint64 frequency = 0;
	
	if (start==0){
		start=SDL_GetPerformanceCounter();
		frequency=SDL_GetPerformanceFrequency();
		return 0.0f;
	}
	
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return (float) ((counter - start) / (double)frequency);
}

void assets_in(void)
{

	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x=(ww/2)-(logo_dst.w/2);
	logo_dst.y=(wh/2)-(logo_dst.h/2);
	//END 	LOGO
	
	//  Set initial values.
	boxLocation 	= 0.0;
	box.x=roundf(boxLocation);

	boxVelocity 	= 12;
	boxWidth 	= 40;
	box.w=roundf(boxWidth);
	box.h=box.w/4;
	box.y=WH-box.h;
	
	initialAltitude = 0;
	ballAltitude 	= initialAltitude;
	ball.w=4;
	ball.h=4;
	ball.y=0+4;
	ballLocation 	= 210.0;
	ball.x=ballLocation;
	time 		= 0.0;
// 	g = 9.81;    // Earth
	 g = 1.624;  //  Moon
	//  g = 24.8;   //  Jupiter
}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
}

//END   FUNCTIONS
