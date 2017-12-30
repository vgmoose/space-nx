#include <time.h>
#include<SDL2/SDL.h>

#include "program.h"
#include "trigmath.h"
#include "draw.h"
#include "images.h"
#include "space.h"

void init(struct Graphics* g)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL init failed: %s\n", SDL_GetError());
		return;
	}

	printf("initialized SDL\n");
	
	g->window = SDL_CreateWindow("n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if(g->window == NULL) {
		printf("window could not be created: %s\n", SDL_GetError());
		return;
	}

	printf("created window\n");
	
	g->window_surface = SDL_GetWindowSurface(g->window);

	printf("got window surface\n");
}

void deinit(struct Graphics* g)
{
	SDL_Delay(10000);

	SDL_DestroyWindow(g->window);

	SDL_Quit();
}

int main(int argc, char *argv[])
{
	printf("Very first main entered\n");
	struct Graphics graphics = {};
	
	printf("Going for graphics\n");
	init(&graphics);
	printf("Graphics initialized\n");
	
	struct SpaceGlobals mySpaceGlobals = {};
	mySpaceGlobals.graphics = &graphics;
	printf("Space globals initialized\n");

	//Flag for restarting the entire game.
	mySpaceGlobals.restart = 1;

	// initial state is title screen
	mySpaceGlobals.state = 1;
	mySpaceGlobals.titleScreenRefresh = 1;

	//Flags for render states
	mySpaceGlobals.renderResetFlag = 0;
	mySpaceGlobals.menuChoice = 0; // 0 is play, 1 is password

	// setup the password list
	unsigned int pwSeed = 27;
	int x;
	for (x=0; x<100; x++)
		mySpaceGlobals.passwordList[x] = (int)(prand(&pwSeed)*100000);
	
	printf("About to set the time\n");
	// set the starting time
	mySpaceGlobals.seed = time(0);
	printf("Set the time!\n");
	
	int error;
//	VPADData vpad_data;
	
	// decompress compressed things into their arrays, final argument is the transparent color in their palette
	decompress_sprite(3061, 200, 100, compressed_title, mySpaceGlobals.title, 39);
//	decompress_sprite(511, 36, 36, compressed_ship, mySpaceGlobals.orig_ship, 14);
//	decompress_sprite(206, 23, 23, compressed_enemy, mySpaceGlobals.enemy, 9);
	
	// setup palette and transparent index
//	mySpaceGlobals.curPalette = ship_palette;
	mySpaceGlobals.transIndex = 14;
    
    mySpaceGlobals.passwordEntered = 0;
	
	// initialize starfield for this game
	initStars(&mySpaceGlobals);
		
	mySpaceGlobals.invalid = 1;
	printf("About to enter main loop\n");
		
//	int a = 0;
//	while(a < 50000)
//	{
//		a++;
////		SDL_Delay(16);
//		
////		VPADRead(0, &vpad_data, 1, &error);
//		
//		//Get the status of the gamepad
////		mySpaceGlobals.button = vpad_data.btns_h;
////		
////		mySpaceGlobals.rstick = vpad_data.rstick;
////		mySpaceGlobals.lstick = vpad_data.lstick;
////		
////		mySpaceGlobals.touched = vpad_data.tpdata.touched;
//		if (mySpaceGlobals.touched == 1)
//		{
////			mySpaceGlobals.touchX = ((vpad_data.tpdata.x / 9) - 11);
////			mySpaceGlobals.touchY = ((3930 - vpad_data.tpdata.y) / 16);
//		}
//		printf("Did one if\n");
//
//		
//		if (mySpaceGlobals.restart == 1)
//		{
//			reset(&mySpaceGlobals);
//			mySpaceGlobals.restart = 0;
//		}
//		
//		printf("Did one if\n");
//		
//		if (mySpaceGlobals.state == 1) // title screen
//		{
////			printf("About to display title screen\n");
			displayTitle(&mySpaceGlobals);
////			printf("menu action\n");
////			doMenuAction(&mySpaceGlobals);
////			printf("done with this\n");
//		}
//		else if (mySpaceGlobals.state == 2) // password screen
//		{
//			displayPasswordScreen(&mySpaceGlobals);
//			doPasswordMenuAction(&mySpaceGlobals);
//		}
//		else if (mySpaceGlobals.state == 3) // pause screen
//		{
//			displayPause(&mySpaceGlobals);
//			doMenuAction(&mySpaceGlobals);
//		}
//		else if  (mySpaceGlobals.state == 4) // game over screen
//		{
//			displayGameOver(&mySpaceGlobals);
//			doMenuAction(&mySpaceGlobals);
//		}
//		else 	// game play
//		{
//			//Update location of player1 and 2 paddles
//			p1Move(&mySpaceGlobals);
//
//			// perform any shooting
//			p1Shoot(&mySpaceGlobals);
//			
//			// handle any collisions
//			handleCollisions(&mySpaceGlobals);
//			
//			// do explosions
//			handleExplosions(&mySpaceGlobals);
//			
//			// if we're out of lives, break
//			if (mySpaceGlobals.lives <= 0 && mySpaceGlobals.state == 4)
//				continue;
//			
//			// add any new enemies
//			addNewEnemies(&mySpaceGlobals);
//			
//			//Render the scene
//			render(&mySpaceGlobals);
//			
//			// check for pausing
//			checkPause(&mySpaceGlobals);
//		}
//		//To exit the game
//		if (mySpaceGlobals.button & BUTTON_HOME)
//		{
//			break;
//		}
//		printf("I'm out\n");
//
//	}
	
	printf("Unloading\n");
	deinit(&graphics);
	printf("Unloaded\n");
}
