#include "input.h"

#if defined(__SWITCH__) && !defined(__LIBNX__)
	#include<libtransistor/nx.h>
#elif defined(__SDL2__)	// just PC
	#include <SDL2/SDL.h>
#else
	#include <SDL/SDL.h>
#endif

void PADInit()
{
	#if defined(__SWITCH__) && !defined(__LIBNX__)
		hid_init();
	#endif
}

void PADDestroy()
{
	#if defined(__SWITCH__) && !defined(__LIBNX__) // switch
		hid_finalize();
	#endif
}

#if defined(__SWITCH__) && !defined(__LIBNX__) // switch
static void readInputInternal(struct PADData* data, hid_controller_state_entry_t ent)
{
	// process inputs
	data->btns_h |= ((ent.button_state & JOYPAD_A)? 		BUTTON_A : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_B)? 		BUTTON_B : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_UP)? 		BUTTON_UP : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_DOWN)? 		BUTTON_DOWN : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_LEFT)? 		BUTTON_LEFT : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_RIGHT)?		BUTTON_RIGHT : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_START)?		BUTTON_PLUS : 0);
	data->btns_h |= ((ent.button_state & JOYPAD_SELECT)?	BUTTON_MINUS : 0);

	// get int values of sticks
	int p1 = ent.left_stick_x, p2 = ent.left_stick_y, p3 = ent.right_stick_x, p4 = ent.right_stick_y;

	// make doubles
	double d1 = (float) p1, d2 = (float) p2, d3 = (float) p3, d4 = (float) p4;

	// update stick values (between -1 and 1 for each)
	data->lstick_x += d1 / 32768.0;
	data->lstick_y += d2 / 32768.0;
	data->rstick_x += d3 / 32768.0;
	data->rstick_y += d4 / 32768.0;
}
#endif

void PADRead(struct PADData* data)
{
	// reset buttons
	data->btns_h = 0b00000000;
	
	#if defined(__SWITCH__) && !defined(__LIBNX__)
		data->lstick_x = 0;
		data->lstick_y = 0;
		data->rstick_x = 0;
		data->rstick_y = 0;

		// scan for controllers (main unit or 1P joycons detached)
		hid_controller_t* num = hid_get_shared_memory()->controllers;		// joycons detached
		hid_controller_t* num8 = hid_get_shared_memory()->controllers + 8;	// main unit

		hid_controller_state_entry_t ent = num->main.entries[num->main.latest_idx];
		hid_controller_state_entry_t ent8 = num8->main.entries[num8->main.latest_idx];
	
		// process inputs
		readInputInternal(data, ent);
		readInputInternal(data, ent8);
	
	#else // libtransistor
		SDL_Event event;
		SDL_PollEvent(&event);
	
		data->lstick_x = 0;
		data->lstick_y = 0;
		data->rstick_x = 0;
		data->rstick_x = 0;
		
		if (event.type == SDL_KEYDOWN)
		{
			#if !defined(__SWITCH__)
				data->btns_h |= ((event.key.keysym.sym == SDLK_RETURN)?		BUTTON_A : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_BACKSPACE)?		BUTTON_B : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_UP)?		BUTTON_UP : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_DOWN)?		BUTTON_DOWN : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_LEFT)?		BUTTON_LEFT : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_RIGHT)?		BUTTON_RIGHT : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_SPACE)?		BUTTON_PLUS : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_DELETE)?		BUTTON_MINUS : 0);

				// update stick values (between -1 and 1 for each)
				data->rstick_x = -1*(event.key.keysym.sym == SDLK_w) + (event.key.keysym.sym == SDLK_s);
				data->rstick_y = -1*(event.key.keysym.sym == SDLK_a) + (event.key.keysym.sym == SDLK_d);
			#else
				data->btns_h |= ((event.key.keysym.sym == SDLK_a)?		BUTTON_A : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_b)?		BUTTON_B : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_UP)?		BUTTON_UP : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_DOWN)?		BUTTON_DOWN : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_LEFT)?		BUTTON_LEFT : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_RIGHT)?		BUTTON_RIGHT : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_PLUS)?		BUTTON_PLUS : 0);
				data->btns_h |= ((event.key.keysym.sym == SDLK_MINUS)?		BUTTON_MINUS : 0);

				// update stick values (between -1 and 1 for each)
//				data->rstick_x = -1*(event.key.keysym.sym == SDLK_w) + (event.key.keysym.sym == SDLK_s);
//				data->rstick_y = -1*(event.key.keysym.sym == SDLK_a) + (event.key.keysym.sym == SDLK_d);
			#endif
		}

	#endif
}