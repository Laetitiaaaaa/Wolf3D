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

void			loop_guide(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE && ct->menu.in != OUT)
	{
		while (SDL_PollEvent(&event))
		{
			((state[SDL_SCANCODE_SPACE]) && (event.type == SDL_KEYDOWN)) ?
			ct->menu.in = OUT : 0;
			(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		copy_texture_menu(ct, "./images/guides.bmp");
		SDL_RenderPresent(ct->rend);
	}
}

void			loop_menu(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		while (SDL_PollEvent(&event))
		{
			limit_menu(ct);
			action_loop_menu(state, event, ct);
			common_actions(ct, state, event);
		}
		update_settings(ct);
		print_menu(ct);
		SDL_RenderPresent(ct->rend);
	}
}

void			loop_fireworks(t_context *ct)
{
	Uint8		*state;
	SDL_Event	event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{
		(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
		(state[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN) ?
		quit("Thank you for playing", ct) : 0;
	}
	draw_fireworks(ct);
}

void			choose_interface(t_context *ct)
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
		draw_icon(ct);
		if (ct->sp.mushroom_nb == ct->total_mushroom_nb)
		{
			ct->choose_inter = FIREWORKS;
			Mix_HaltMusic();
			Mix_PlayChannel(MIX_DEFAULT_CHANNELS, ct->chunky, -1);
		}
	}
	if (ct->choose_inter == FIREWORKS)
		loop_fireworks(ct);
}

void			loop(t_context *ct)
{
	Uint8			*state;
	unsigned int	last_time;
	unsigned int	delta_time;
	unsigned int	one_second_count;
	unsigned int	fps_count;

	last_time = 0;
	state = (Uint8*)SDL_GetKeyboardState(NULL);
	one_second_count = 0;
	fps_count = 0;
	manage_music(ct);
	while (ct->menu.in != OUT)
	{
		delta_time = SDL_GetTicks() - last_time;
		last_time += delta_time;
		delta_time < FRAME_TIME ? SDL_Delay(FRAME_TIME - delta_time) : 0;
		fps_count++;
		one_second_count += delta_time;
		if (one_second_passed(ct, one_second_count, fps_count) == TRUE)
		{
			one_second_count = 0;
			fps_count = 0;
		}
		action_loop_game(ct, state, delta_time);
	}
}
