/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/22 10:43:03 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	action_loop_game(t_context *ct)
{
		ct->cam.angle = angle_limit(ct->cam.angle);
		SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
		SDL_RenderClear(ct->rend);
		choose_interface(ct);
		SDL_RenderPresent(ct->rend);
}

void	loop(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	delta_time;
	unsigned int frame_time;

	frame_time = 1000 / 60;

	int		count;
	unsigned int i = 0;

	count = 0;

	last_time = 0;
	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (ct->menu.in != OUT)
	{
		delta_time = SDL_GetTicks() - last_time;
		last_time += delta_time;
		if (delta_time < frame_time)
			SDL_Delay(frame_time);
		while (SDL_PollEvent(&event))
		{
			((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN)) ? ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		key_events(ct, state, delta_time);
		action_loop_game(ct);
		count++;
		i += delta_time;

		if (i >1000)
		{
			// printf("count%d\n", count ); //fps
			count = 0;
			i =0;
		}
	}
}

void	choose_interface(t_context *ct)
{
	if (ct->choose_inter == MAP)
	{

		draw_2d(ct);
		if (ct->at_least_one_sprite == TRUE)
			draw_sprite_in_2d(ct);
	}
	if (ct->choose_inter == GAME)
	{
		draw_background(ct);
		draw_wall(ct);
		if (ct->at_least_one_sprite == TRUE)
			draw_sprite_in_3d(ct);
	}
}