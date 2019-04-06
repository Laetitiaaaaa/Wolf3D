
#include "wolf3d.h"

void	common_actions(t_context *ct, Uint8 *state, SDL_Event event)
{
	((state[SDL_SCANCODE_1]) && (event.type == SDL_KEYDOWN)) ? ct->full_screen = -ct->full_screen : 0;
	(state[SDL_SCANCODE_M] && event.type == SDL_KEYDOWN) ? ct->mute = -ct->mute : 0;
	(state[SDL_SCANCODE_9] && event.type == SDL_KEYDOWN) ? ct->volume-- : 0;
	(state[SDL_SCANCODE_0] && event.type == SDL_KEYDOWN) ? ct->volume++ : 0;
	(state[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN) ? quit("Thank you for playing", ct) : 0;
}

void	update_settings(t_context *ct)
{
	while (ct->volume < 0)
		ct->volume++;
	Mix_VolumeMusic(ct->volume);
	Mix_VolumeChunk(ct->chunk, ct->volume);
	(ct->mute < 0) ? Mix_PauseMusic() : Mix_ResumeMusic();
	if (ct->full_screen < 0)
	{
		SDL_SetWindowFullscreen(ct->window, SDL_WINDOW_FULLSCREEN);
		SDL_GetWindowSize(ct->window, &ct->xwin, &ct->ywin);
	}
	if (ct->full_screen > 0)
	{
		ct->xwin = XWIN;
		ct->ywin = YWIN;
		SDL_SetWindowSize(ct->window, ct->xwin, ct->ywin);
		SDL_SetWindowFullscreen(ct->window, 0);
		SDL_RestoreWindow(ct->window);
	}
}

void	limit_menu(t_context *ct)
{
	while (ct->menu.in > 2)
		ct->menu.in -= 2;
	while (ct->menu.in < 0)
		ct->menu.in += 3;
}

void	loop_menu(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		while (SDL_PollEvent(&event))
		{
			limit_menu(ct);
			((state[SDL_SCANCODE_DOWN]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in + 1) % OUT : 0;
			((state[SDL_SCANCODE_UP]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in - 1) % OUT : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == PLAY)) ? loop(ct) : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == GUIDE)) ? loop_guide(ct) : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == QUIT)) ? quit("Thank you for playing", ct) : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		print_menu(ct);
		SDL_RenderPresent(ct->rend);
	}
}

void	loop_guide(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE && ct->menu.in != OUT)
	{
		while (SDL_PollEvent(&event))
		{
			((state[SDL_SCANCODE_SPACE]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = OUT : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		copy_texture_menu(ct, "./images/guides.bmp");
		SDL_RenderPresent(ct->rend);
	}
}
