//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION:
 * Gravity 1
 * Dropping a bowling ball from a crane,
 * applying gravity
 * 
 * press left mouse button to reset
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

//Real Size in SI-Unit centimeters
#define REALSIZE_H 	20
#define REALSIZE_V 	 5

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
SDL_Surface    *temp_surface	= NULL;
//BEGIN VISIBLES
SDL_Rect 	box;

TTF_Font       *font		= NULL;
struct entity_static 	sb_desc;

struct entity_dyn 	bullet;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
int  gcd	(int, int);
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
//BEGIN WINDOW
char title[10];
query_disp();
//BEGIN SCALING
int gcd_;
gcd_= gcd(REALSIZE_H,REALSIZE_V);
IARH=REALSIZE_V/gcd_;
IARW=REALSIZE_H/gcd_;
SDL_Log("Aspect Ratio: %d:%d",IARW,IARH);
//END SCALING
assets_in();
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
sprintf(title, "%dx%d cm",(int)REALSIZE_H,(int)REALSIZE_V);
SDL_SetWindowTitle(Window, title);
SDL_ShowWindow(Window);
//END WINDOW
float currentTime = 0.0f;
float accumulator = 0.0f;

SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){
	static char set = 1;
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

				accumulator=0;
				bullet.data.frac.pos.x	= -bullet.data.frac.size.x;
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

	//BEGIN LOGIC
	float newTime   = time_();
	float deltaTime = newTime - currentTime;
	currentTime     = newTime;
	accumulator    += deltaTime;

	if (bullet.data.frac.pos.x + bullet.data.frac.size.x <= ww)
		bullet.data.frac.pos.x+=bullet.vel.x*deltaTime;
	//The result is pretty good.

	if (set){
		if (bullet.data.frac.pos.x + bullet.data.frac.size.x >= ww){
// 			SDL_Log("deltaTime: %f", deltaTime);
			SDL_Log("accumulator: %f", accumulator);
			set=0;
		}
	}
	bullet.data.dst.x=ceilf(bullet.data.frac.pos.x);
	//END LOGIC

	//BEGIN RENDERING
	SDL_SetRenderDrawColor(Renderer, BG);
	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, bullet.data.Texture, NULL, &bullet.data.dst);
	SDL_RenderCopy(Renderer, sb_desc.Texture, NULL, &sb_desc.dst);
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
	int w,h;
	//BEGIN BULLET
	temp_surface = IMG_Load("./assets/gfx/bullet.png");
	bullet.data.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(bullet.data.Texture, NULL, NULL, &w, &h);
	/*
	 * 1 cm gonna 1 cm
	 * so the scale is: 1:1
	 * bullet diameter: 0.785 cm
	 * Muzzle velocity: 800 m/s (2,625 ft/s)
	 * 
	 */
	bullet.data.frac.size.y	= 0.785 / CENTI_PER_INCH * dpi.y;
	float w_helper 		= h / (0.785 / CENTI_PER_INCH * dpi.y);
	bullet.data.frac.size.x	= w/w_helper;
	bullet.data.frac.pos.y	= (float)wh/2 - bullet.data.frac.size.y/2;
	bullet.data.frac.pos.x	= 0-bullet.data.frac.size.x;
	
	rect_round(&bullet.data);
	
	bullet.vel.y = 0;
	bullet.vel.x = 80000; 	//800 m/s | 800*100 = cm/s | 80,000 cm/s
				//we got a 20 cm Window
				//so if we want to see something we better slow things down
				//Let's say the bullet passes the screen in 4 seconds.
				//so it moves with 5 cm per second
				
				//so with the numbers we travel pixels/acutally verticies
				//that exist somewhere in the RAM
				//again we need to know how many pixels are a cm.
	bullet.vel.x = 5.0 * (dpi.x/CENTI_PER_INCH);
	SDL_Log("bullet.vel.x: %f", bullet.vel.x);
	//END 	BULLET
	
	//BEGIN SB_DESC
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 16);
	SDL_Color color={BLACK};
	char text[]="Desired speed: 5 cm/s";
	temp_surface=TTF_RenderText_Blended(font,text,color);
	sb_desc.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(sb_desc.Texture, NULL, NULL, &sb_desc.dst.w, &sb_desc.dst.h);
	sb_desc.dst.x=200;
	sb_desc.dst.y=100;
	//END 	SB_DESC
}
void assets_out(void)
{
	SDL_DestroyTexture(bullet.data.Texture);
	TTF_CloseFont(font);
}

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

int gcd (int a, int b)
{
	
	return (b == 0) ? a : gcd (b, a%b);
	
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
	s_entity->dst.w=roundf(s_entity->frac.size.x)    ;
	s_entity->dst.h=roundf(s_entity->frac.size.y)    ;
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
