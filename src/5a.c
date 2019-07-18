//BEGIN HEAD

//BEGIN DESCRIPTION

/* DESCRIPTION:
 * Clear the board, meassure Rendering
 * Timing precision: float
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
float time_	(void);
void update	(float);
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
float currentTime = 0.0f;
float time_acc = 0.0f;

SDL_Event event;
int running 	= 1;
int updates 	= 0;
int updates_acc	= 0;
int pictures 	= 0;
int pictures_acc	= 0;

float counter = 0;
SDL_SetRenderDrawColor(Renderer, BG);
SDL_RenderClear(Renderer);
//END   INIT

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
					
				default:
					break;
			}
		}
	}


	//BEGIN RENDERING
	pictures++;
	SDL_RenderPresent(Renderer);
	//END   RENDERING

	float newTime   		=  time_();
	float deltaTime 		=  newTime - currentTime;
	currentTime     		=  newTime;
	time_acc    			+= deltaTime;
	counter				+= deltaTime;
	// update				   (deltaTime);
	updates ++;
	if (counter>1.0){
		SDL_Log("counter: %f",counter);
		SDL_Log("updates: %d",updates);
		SDL_Log("pictures: %d",pictures);
		counter = counter - 1.0;
		updates_acc += updates;
		updates = 0;
		pictures_acc += pictures;
		pictures = 0;
		
	}
}
//END   MAIN LOOP
SDL_Log("AT: %.2f", time_acc);
SDL_Log("AU: %d", updates_acc);
SDL_Log("AP: %d", pictures_acc);
//BEGIN EXIT
exit_();
return EXIT_SUCCESS;
//END 	EXIT

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS

//BEGIN UPDATE
void update(float dt)
{
	SDL_Log("DT: %.10f", dt);
}

float time_(void)
{
	
	static Uint64 	start = 0;
	static float 	frequency = 0;
	
	if (start==0){
		start	 = SDL_GetPerformanceCounter();
		frequency= (float)SDL_GetPerformanceFrequency();
		return 0.0f;
	}
	
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return  (((float)counter - (float)start) /frequency);
}
//END 	UPDATE


//END   FUNCTIONS
