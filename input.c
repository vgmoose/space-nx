#include "input.h"

#include <SDL2/SDL.h>

void PADInit()
{

}

void PADDestroy()
{

}

void PADRead(struct PADData* data)
{
	// reset buttons
	data->btns_h = 0b00000000;

	data->lstick_x = 0;
	data->lstick_y = 0;
	data->rstick_x = 0;
	data->rstick_y = 0;


	// keep polling until a null event is reached
	// this allows us to get multiple buttons for a single frame
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_JOYBUTTONDOWN)
		{
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_A)?				PAD_BUTTON_A 			: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_B)?				PAD_BUTTON_B 			: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)?				PAD_BUTTON_UP 		: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_MAX)?			PAD_BUTTON_DOWN 	: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)?			PAD_BUTTON_LEFT 	: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)?		PAD_BUTTON_RIGHT 	: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)?		PAD_BUTTON_PLUS 	: 0);
			data->btns_h |= ((event.jbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)?		PAD_BUTTON_MINUS 	: 0);
		}

		if (event.type == SDL_JOYAXISMOTION)
		{
			// update stick values (between -1 and 1 for each)
			if (event.jaxis.axis == 0) data->lstick_x += (event.jaxis.value / 32767.0f);
			if (event.jaxis.axis == 1) data->lstick_y -= (event.jaxis.value / 32767.0f);
			if (event.jaxis.axis == 2) data->rstick_x += (event.jaxis.value / 32767.0f);
			if (event.jaxis.axis == 3) data->rstick_y -= (event.jaxis.value / 32767.0f);
		}

		if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION)
		{
			data->touched = 1;
			data->touched_y = event.tfinger.y * 720;
			data->touched_x = event.tfinger.x * 1280;
		}

		if (event.type == SDL_FINGERUP)
		{
			data->touched = 0;
		}

	}
}
