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

void	loop(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	delta_time;

	last_time = 0;
	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		delta_time = SDL_GetTicks() - last_time;
		last_time += delta_time;
		while (SDL_PollEvent(&event))
			if ((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN))
				ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB;
		key_events(ct, state, delta_time);
		ct->cam.angle = angle_limit(ct->cam.angle);
		SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
		SDL_RenderClear(ct->rend);
		choose_interface(ct);
		SDL_RenderPresent(ct->rend);

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
		{
			draw_sprite_in_3d(ct);
		}
	}
	// if (ct->choose_inter == MENU)
	// {
	// 	print_menu(ct);
	// }
}

static void	key_events_2d(t_context *ct, Uint8 *state, unsigned int delta_time)
{
	if ((ct->cam.posi.y - 0.005 > 0)
		&& ct->mpp.map[(int)(ct->cam.posi.y - 0.005)][(int)ct->cam.posi.x] != 1)
		state[SDL_SCANCODE_I] ? ct->cam.posi.y -= 1.0 * delta_time / 1000 : 0;
	if ((ct->cam.posi.y + 0.005 < ct->mpp.y)
		&& ct->mpp.map[(int)(ct->cam.posi.y + 0.005)][(int)ct->cam.posi.x] != 1)
		state[SDL_SCANCODE_K] ? ct->cam.posi.y += 1.0 * delta_time / 1000 : 0;
	if ((ct->cam.posi.x - 0.005 > 0)
		&& ct->mpp.map[(int)ct->cam.posi.y][(int)(ct->cam.posi.x - 0.005)] != 1)
		state[SDL_SCANCODE_J] ? ct->cam.posi.x -= 1.0 * delta_time / 1000 : 0;
	if ((ct->cam.posi.x + 0.005 < ct->mpp.x)
		&& ct->mpp.map[(int)ct->cam.posi.y][(int)(ct->cam.posi.x + 0.005)] != 1)
		state[SDL_SCANCODE_L] ? ct->cam.posi.x += 1.0 * delta_time / 1000 : 0;
}

static void	key_events_3d(t_context *ct, Uint8 *state, unsigned delta_time)
{
	float	d;
	float	dx;
	float	dy;

	d = 0.005;
	dy = d * sin(convert_deg_to_rad(ct->cam.angle));
	dx = d * cos(convert_deg_to_rad(ct->cam.angle));
	if ((ct->cam.posi.y - dy > 0) && (ct->cam.posi.y - dy < ct->mpp.y)
		&& (ct->cam.posi.x + dx < ct->mpp.x) && (ct->cam.posi.x + dx > 0)
		&& ct->mpp.map[(int)(ct->cam.posi.y - dy)][(int)(ct->cam.posi.x + dx)] != 1)
	{
		if (state[SDL_SCANCODE_UP])
		{
			ct->cam.posi.y -= dy * (float)delta_time / 2.0;
			ct->cam.posi.x += dx * (float)delta_time / 2.0;
		}
	}
	if ((ct->cam.posi.y + dy < ct->mpp.y) && (ct->cam.posi.y + dy > 0) && (ct->cam.posi.x - dx > 0) && (ct->cam.posi.x - dx < ct->mpp.x)
		&& ct->mpp.map[(int)(ct->cam.posi.y + dy)][(int)(ct->cam.posi.x - dx)] != 1)
	{
		if (state[SDL_SCANCODE_DOWN])
		{
			ct->cam.posi.y += dy * (float)delta_time / 2.0;
			ct->cam.posi.x -= dx * (float)delta_time / 2.0;
		}
	}
}

void	key_events(t_context *ct, Uint8 *state, unsigned int delta_time)
{
	state[SDL_SCANCODE_ESCAPE] ? quit("Thank you for playing", ct) : 0;
	state[SDL_SCANCODE_LEFT] ? ct->cam.angle += 50.0 * delta_time/1000 : 0;
	state[SDL_SCANCODE_RIGHT] ? ct->cam.angle -= 50.0 * delta_time/1000 : 0;
	key_events_2d(ct, state, delta_time);
	key_events_3d(ct, state, delta_time);
}


