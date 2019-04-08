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

void	show_fps(t_context *ct)
{
	SDL_Color		color = {0, 0, 0,  SDL_ALPHA_OPAQUE};
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	char 			*s;

	s = ft_itoa(ct->fps);
	surface = TTF_RenderText_Solid(ct->font, s, color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	SDL_FreeSurface(surface);
	SDL_Rect dst= {500, 20, 40, 40};
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
	free(s);
	s = NULL;
}

void	loop_fireworks(t_context *ct)
{
	Uint8 	*state;
	SDL_Event event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
		(state[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN) ? quit("Thank you for playing", ct) : 0;
	}
	draw_fireworks(ct);
}

static void	choose_interface(t_context *ct)
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

static void	action_loop_game(t_context *ct, Uint8 *state, unsigned int delta_time)
{
	SDL_Event		event;

	while (SDL_PollEvent(&event))
	{
		((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN)) ? ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB : 0;
		(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
		common_actions(ct, state, event);
	}
	ct->cam.angle = angle_limit(ct->cam.angle);
	SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ct->rend);
	choose_interface(ct);
	if (ct->show_fps == TRUE)
		show_fps(ct);
	SDL_RenderPresent(ct->rend);
	update_settings(ct);
	key_events(ct, state, delta_time);

}

void	loop(t_context *ct)
{
	Uint8			*state;
	unsigned int	last_time;
	unsigned int	delta_time;
	unsigned int 	one_second_count;
	unsigned int	fps_count;

	last_time = 0;
	state = (Uint8*)SDL_GetKeyboardState(NULL);

	one_second_count = 0;
	fps_count = 0;
	Mix_PlayMusic(ct->music, -1);
	while (ct->menu.in != OUT)
	{
		delta_time = SDL_GetTicks() - last_time;
		last_time += delta_time;
		delta_time < FRAME_TIME ? SDL_Delay(FRAME_TIME - delta_time) : 0;
		fps_count++;
		one_second_count += delta_time;
		if (one_second_count > 1000)
		{
			ct->fps = fps_count;
			one_second_count = 0;
			fps_count = 0;
		}
		action_loop_game(ct, state, delta_time);
	}
}

