//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION:
 * 
 * Window Size in SI-Units
 *
 * DEFINED PROGRESS GOALS:
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

//DPI is Dots per Inch - Industry should fix that
#define CENTI_PER_INCH 2.54
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
struct scalar2{
	float x;
	float y;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
int 		ww;
int 		wh;

struct scalar2  dpi;
SDL_Rect 	box;

//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void query_disp (void);
void assets_in	(void);
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
// SDL_SetWindowPosition(Window,0,0);
// SDL_SetWindowSize(Window,ww,wh);
char title[10];
query_disp();
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
sprintf(title, "%dx%d cm",(int)REALSIZE_H,(int)REALSIZE_V);
SDL_SetWindowTitle(Window, title);
SDL_ShowWindow(Window);
//END WINDOW

//giving Box a size in centimeters
box.w		= roundf(2.0/CENTI_PER_INCH*dpi.x);
box.h		= roundf(2.0/CENTI_PER_INCH*dpi.y);

box.x		= ww/2-box.w/2;
box.y		= wh/2-box.h/2;

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
	//END LOGIC

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, WHITE);
	SDL_RenderClear(Renderer);

	SDL_SetRenderDrawColor(Renderer, BLUE);
	SDL_RenderFillRect(Renderer, &box);

	SDL_RenderPresent(Renderer);
	//END   RENDERING
	
}
//END   MAIN LOOP
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void query_disp	(void)
{
	int disp;
	
	disp=SDL_GetWindowDisplayIndex(Window);
	SDL_GetDisplayDPI(disp, NULL,&dpi.x, &dpi.y);
	
	SDL_Log("hdpi: %f", dpi.x);
	ww=roundf(REALSIZE_H/CENTI_PER_INCH*dpi.x);

	SDL_Log("vdpi: %f", dpi.y);
	wh=roundf(REALSIZE_V/CENTI_PER_INCH*dpi.y);
	SDL_Log("w: %d, h: %d",ww,wh);
	SDL_SetWindowSize(Window, ww,wh);
	
}
//END   FUNCTIONS
