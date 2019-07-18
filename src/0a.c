//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION:
 * 
 * Linear Scaling
 * https://en.wikipedia.org/wiki/Linear_scale
 * https://en.wikipedia.org/wiki/Scale_(map)
 * 
 * The scale of a map is the ratio of a distance on the map to the corresponding
 * distance on the ground.
 * 
 * DEFINED PROGRESS GOALS:
 * 
 * 	Bring up a scaling bar
 * 	consisting of rects and describe it with ttf
 * 
 * 	set up a arithmetic scaling
 * 	show the result
 * 	Tree, elephant, yacht
 * 
 * 
 * The tree has a height of 30 m in real
 * in the window he gonna be 15 cm
 * that means:
 * 1 cm gonna be 2 m
 * Scale: 1:200
 * 
 * NEXT:
 * - make window resizeable
 * - change scale with mousewheel
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

//Real Size in SI-Unit centimeters
#define REALSIZE_H 	16.0*2
#define REALSIZE_V 	 9.0*2

//DPI is Dots per Inch - Industry should fix that
#define CENTI_PER_INCH 	2.54

#define TREE_HEIGHT	30.0	//metres

// #define MAX_VIS_HEIGHT 	35	//metres
//The window widht gonna depend on MAX_VIS_HEIGHT
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//This one is not necessary for real code, redundant with vec2.
//just let it here because it is more descriptive since lenght is a skalar
struct scalar2{
	float x;
	float y;
};

struct vec2{
	float x;
	float y;
};
//to be more presize one could use scalar2 here in, instead of
//vec2 size
struct rect{
	struct vec2 pos;
	struct vec2 size;
};

struct entity_static{
	SDL_Texture    *Texture;
	struct rect 	frac;
	SDL_Rect 	dst;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
int 		ww;
int 		wh;
int 		IARH;  				//Image Aspect Ratio horizontal
int 		IARW;  				//Image Aspect Ratio vertical
struct scalar2  dpi;
SDL_Surface    *temp_surface	= NULL;
//BEGIN VISIBLES
SDL_Rect 	box;

TTF_Font       *font		= NULL;
struct entity_static sb_desc;

struct entity_static tree;
struct entity_static elephant;
struct entity_static yacht;

struct entity_static sbr[8];
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
int  gcd	(int, int);
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
	SDL_SetRenderDrawColor(Renderer, BG);
	SDL_RenderClear(Renderer);

	//BEGIN SCALING BAR
	for (int i=0; i<8; i++){
		if (i%2){
			SDL_SetRenderDrawColor(Renderer, WHITE);
			SDL_RenderFillRect(Renderer, &sbr[i].dst);
			SDL_SetRenderDrawColor(Renderer, BLACK);
			SDL_RenderDrawRect(Renderer, &sbr[i].dst);
		}else{
			SDL_SetRenderDrawColor(Renderer, BLACK);
			SDL_RenderFillRect(Renderer, &sbr[i].dst);
		}
	}
	//END 	SCALING BAR
	SDL_RenderCopy(Renderer, sb_desc.Texture, NULL, &sb_desc.dst);
	
	SDL_RenderCopy(Renderer, tree.Texture, NULL, &tree.dst);
	//Flip the elephant for the shadows
	SDL_RenderCopyEx(Renderer, elephant.Texture, NULL, &elephant.dst, 0, NULL, 1);
	//SDL_RenderCopy(Renderer, elephant.Texture, NULL, &elephant.dst);
	SDL_RenderCopy(Renderer, yacht.Texture, NULL, &yacht.dst);
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
	//Load need Images, make them textures and init their dest-rects
	int w,h;
	//BEGIN TREE
	temp_surface = IMG_Load("./assets/gfx/tree.png");
	tree.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(tree.Texture, NULL, NULL, &w, &h);
	/*
	 * The tree has a height of 30 m in real.
	 * In the window he gonna be 15 cm.
	 * that means:
	 * 1 cm gonna be 2 m
	 * Scale: 1:200
	 *
	 * We know that 1 cm in the window gonna be 200 cm in real,
	 * so how many cm's are 30 m's?
	 * First we want to know how many cm's are one meter,
	 * it 1 cm devided be 2m or * 0.5
	 * TREE_HEIGHT * 0.5 = 15 cm
	 * 
	 */
	tree.dst.h	= roundf(TREE_HEIGHT*0.5 / CENTI_PER_INCH*dpi.y);
	SDL_Log		  ("Tree height: %d in Pixel's", tree.dst.h);
	float w_helper 	= h/(TREE_HEIGHT*0.5 / CENTI_PER_INCH*dpi.y);
	tree.dst.w	= w/w_helper;
	tree.dst.y	= wh-tree.dst.h;
	//Let's set the tree 5 meters to the right
	tree.dst.x	= roundf(5*0.5/CENTI_PER_INCH*dpi.x);
	//END 	TREE
	
	//BEGIN ELEPHANT
	temp_surface 	= IMG_Load("./assets/gfx/elephant_s.png");
	elephant.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(elephant.Texture, NULL, NULL, &w, &h);
	
	float real_height=3.3; //m
	elephant.dst.h	= roundf(real_height*0.5 / CENTI_PER_INCH*dpi.y);
	w_helper 	= h/(real_height*0.5 / CENTI_PER_INCH*dpi.y);
	elephant.dst.w	= w/w_helper;
	elephant.dst.x	= tree.dst.w;
	elephant.dst.y	= wh-elephant.dst.h;
	//END 	ELEPHANT

	//BEGIN YACHT
	temp_surface = IMG_Load("./assets/gfx/yacht.png");
	yacht.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(yacht.Texture, NULL, NULL, &w, &h);
	
	float real_lenght=21.7; //m
	yacht.dst.w	= roundf(real_lenght*0.5 / CENTI_PER_INCH*dpi.x);
	float h_helper 	= w/(real_lenght*0.5 / CENTI_PER_INCH*dpi.x);
	yacht.dst.h	= h/h_helper;
	yacht.dst.x	= (elephant.dst.w+elephant.dst.x)+elephant.dst.w;
	yacht.dst.y	= wh-yacht.dst.h;
	//END 	YACHT

	//BEGIN SCALE BAR RECT
	sbr[0].dst.w 	= roundf(0.5 / CENTI_PER_INCH*dpi.x);
	sbr[0].dst.h	= sbr[0].dst.w/3;
	sbr[0].dst.x	= sbr[0].dst.w*2;
	sbr[0].dst.y	= sbr[0].dst.w*4;

	for (int i=1; i<8; i++){
		sbr[i].dst.w=sbr[0].dst.w;
		sbr[i].dst.h=sbr[0].dst.h;
		sbr[i].dst.y=sbr[0].dst.y;
		
		sbr[i].dst.x=sbr[0].dst.x + (sbr[0].dst.w*i);
	}
	//END 	SCALE BAR RECT
	
	//BEGIN SB_DESC
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 16);
	SDL_Color color={BLACK};
	char text[]="Scale: 1: 200  -  1 cm on the picture are 200 cm in real.";
// 	sprintf(text, "Scale: 1:200");
	temp_surface=TTF_RenderText_Blended(font,text,color);
	sb_desc.Texture = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(sb_desc.Texture, NULL, NULL, &sb_desc.dst.w, &sb_desc.dst.h);
	sb_desc.dst.x=sbr[0].dst.x;
	sb_desc.dst.y=sbr[0].dst.y-sbr[0].dst.h-sb_desc.dst.h;
	//END 	SB_DESC
}
void assets_out(void)
{
	SDL_DestroyTexture(tree.Texture);
	SDL_DestroyTexture(elephant.Texture);
	SDL_DestroyTexture(yacht.Texture);
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
//END   FUNCTIONS
