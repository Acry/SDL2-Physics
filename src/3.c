//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION:
 * 
 * Gravity 1
 * Calculating Earth's gravity.
 * Calculate falling time.
 * Dropping a container from a tower crane,
 * applying gravity
 * 
 * press left mouse button to start falling
 * press right mouse button to reset
 * 
 * This Demo also shows why we need interpoltion (prediction) and derivates.
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

//Real Size in SI-Unit meters
#define REALSIZE_H 	82.1305
#define REALSIZE_V 	52.8554

#define SCALE_RATIO		4.0

//Real Size in SI-Unit centimeters
#define SCALE_UNITS		100.0

#define SCALESIZE_H 	REALSIZE_H/SCALE_RATIO
#define SCALESIZE_V 	REALSIZE_V/SCALE_RATIO

//DPI is Dots per Inch - Industry should fix that
#define CENTI_PER_INCH 	2.54
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
struct vec2{
	float x;
	float y;
};

struct rect{
	struct vec2 pos;
	struct vec2 size;
};

struct entity_static{
	SDL_Texture    *Texture;
	struct rect 	frac;
	SDL_Rect 	dst;
};

struct entity_dyn{
	struct entity_static data;
	struct vec2 	vel;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
int 		ww;
int 		wh;

int 		IARH;  				//Image Aspect Ratio horizontal
int 		IARW;  				//Image Aspect Ratio vertical

float g;
struct vec2  	dpi;

float screen_centimeter_x;
float screen_centimeter_y;

float real_meter_x;
float real_meter_y;

float distance_m;
float distance_p;

SDL_Surface    *temp_surface	= NULL;
//BEGIN VISIBLES


TTF_Font       *font		= NULL;
struct entity_static 	sb_desc;
struct entity_static 	tower_crane;
struct entity_dyn	box;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void query_disp (void);
void assets_in	(void);
void assets_out	(void);
float time_	(void);
void rect_round		(struct entity_static *s_entity);
void earth_gravity(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT

init();
query_disp();
earth_gravity();
SDL_Log("Gravity: %.2f m/s²", g);
assets_in();

//BEGIN WINDOW

char title[20];
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
sprintf(title, "%.2f x %.2f cm",SCALESIZE_H,SCALESIZE_V);
SDL_SetWindowTitle(Window, title);
SDL_ShowWindow(Window);

//END WINDOW
float currentTime = 0.0f;
float accumulator = 0.0f;

SDL_Event event;
int running = 1;
float Altitude=distance_m;
//END   INIT

//BEGIN MAIN LOOP
while(running){
	static char set = 0;
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
				box.data.frac.pos.y 	= (float)wh-(real_meter_y*distance_m)-box.data.frac.size.y;
				box.data.dst.y		= ceilf(box.data.frac.pos.y);

			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){

				accumulator=0;
				Altitude=distance_m;
				set=1;
				break;
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

	float newTime   = time_();
	float deltaTime = newTime - currentTime;
	currentTime     = newTime;
	accumulator    += deltaTime;
if (set){
	if (Altitude > 0.0f){
		//Box Altitude dropping over time
		Altitude = distance_m - 0.5 * g * accumulator * accumulator;
		SDL_Log("Altitude: %f", Altitude);
		SDL_Log("accumulator: %f", accumulator);
		
		box.data.frac.pos.y 	= (float)wh-(real_meter_y*Altitude)-box.data.frac.size.y;
		box.data.dst.y		=  ceilf(box.data.frac.pos.y);
	}
}

	

	

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, BG);
	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, tower_crane.Texture, 	NULL, &tower_crane.dst);
	SDL_RenderCopy(Renderer, box.data.Texture, 	NULL, &box.data.dst);
	SDL_RenderCopy(Renderer, sb_desc.Texture, 	NULL, &sb_desc.dst);
	SDL_RenderPresent(Renderer);
	//END   RENDERING
	
}
//END   MAIN LOOP
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{
	//BEGIN TOWER CRANE
	temp_surface = IMG_Load("./assets/gfx/tower_crane.png");
	tower_crane.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	tower_crane.frac.size.y	= wh;
	tower_crane.frac.size.x	= ww;
	tower_crane.frac.pos.y	= 0;
	tower_crane.frac.pos.x	= 0;
	rect_round(&tower_crane);
	//END 	TOWER_CRANE
	
	//How many pixels are one centimeter on the screen?
	screen_centimeter_x = (SCALESIZE_H * SCALE_RATIO / CENTI_PER_INCH * dpi.x) / REALSIZE_H;
	SDL_Log("pixels are one centimeter on the picture x: %f", screen_centimeter_x);
	screen_centimeter_y = (SCALESIZE_V * SCALE_RATIO / CENTI_PER_INCH * dpi.y) / REALSIZE_V;
	SDL_Log("pixels are one centimeter on the picture y: %f", screen_centimeter_y);
	
	//How many pixels are one real meter?
	float screen_size_x=SCALESIZE_H / CENTI_PER_INCH * dpi.x; //it is ww, just repeated for precision
	float screen_size_y=SCALESIZE_V / CENTI_PER_INCH * dpi.y; //it is wh, just repeated for precision
	
	SDL_Log("screen_size_y: %f", screen_size_y);
	
	real_meter_x=screen_size_x/REALSIZE_H;
	SDL_Log("real_meter_x in pixels: %f", real_meter_x);

	real_meter_y=screen_size_y/REALSIZE_V;
	SDL_Log("real_meter_y in pixels: %f", real_meter_y);
	
	//BEGIN TESTBOX
	temp_surface = IMG_Load("./assets/gfx/container.png");
	box.data.Texture=SDL_CreateTextureFromSurface(Renderer, temp_surface);
	box.data.frac.size.y	= real_meter_x*2.5;
	box.data.frac.size.x	= real_meter_y*8;
	box.data.frac.pos.x	= real_meter_x*67.5;

	box.data.frac.pos.y	= real_meter_y*12.3;
	rect_round(&box.data);
	box.vel.y = 0;
	box.vel.x = 0;
	//END 	TESTBOX

	//falling distance in real meters
	distance_m=(screen_size_y-box.data.frac.pos.y-box.data.frac.size.y)/real_meter_y;
	SDL_Log("falling distance: %.2f m.", distance_m);

	distance_p=(screen_size_y-box.data.frac.pos.y-box.data.frac.size.y);
	SDL_Log("falling distance in pixel: %f", distance_p);

	// These are the expected results for our values:
	float fall_time	= sqrtf(2 * distance_m / g);
	SDL_Log("fall time: %f seconds", fall_time);
	// t 3,0142
	// v 29,5596 m/s
	//   106,4147 km/h

	//BEGIN SB_DESC
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 16);
	SDL_Color color={BLACK};
	char text[30];
	sprintf(text, "Map scale = 1: %.0f cm",SCALE_RATIO*SCALE_UNITS);
	temp_surface=TTF_RenderText_Blended(font,text,color);
	sb_desc.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(sb_desc.Texture, NULL, NULL, &sb_desc.dst.w, &sb_desc.dst.h);
	sb_desc.dst.x=ww-sb_desc.dst.w-50;
	sb_desc.dst.y=25;
	//END 	SB_DESC
}

void assets_out(void)
{
	SDL_DestroyTexture(tower_crane.Texture);
	SDL_DestroyTexture(box.data.Texture);
	TTF_CloseFont(font);
}

void query_disp	(void)
{
	int disp;
	
	disp=SDL_GetWindowDisplayIndex(Window);
	SDL_GetDisplayDPI(disp, NULL,&dpi.x, &dpi.y);
	SDL_Log("hdpi: %f", dpi.x);
	ww=roundf(SCALESIZE_H / CENTI_PER_INCH * dpi.x);
	SDL_Log("vdpi: %f", dpi.y);
	wh=roundf(SCALESIZE_V / CENTI_PER_INCH * dpi.y);
	SDL_Log("w: %d, h: %d",ww,wh);
	SDL_SetWindowSize(Window, ww,wh);
	
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

void rect_round(struct entity_static *s_entity)
{
	s_entity->dst.x=roundf(s_entity->frac.pos.x);
	s_entity->dst.y=roundf(s_entity->frac.pos.y);
	s_entity->dst.w=roundf(s_entity->frac.size.x);
	s_entity->dst.h=roundf(s_entity->frac.size.y);
}

void earth_gravity(void)
{
	//calculating the accelleration with which an object is moving towards
	//to the centre of the earth
	float earth_mass	= 5.9736e+24;	//in kg
	float earth_radius	= 6.375e+6;	//in km
	float gc		= 6.674e-11;	//gravitational constant
	g=(gc*earth_mass)/(earth_radius*earth_radius);
}
//END   FUNCTIONS
