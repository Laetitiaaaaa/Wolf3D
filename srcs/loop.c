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

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		while (SDL_PollEvent(&event))
		{
			if ((state[SDL_SCANCODE_C]) && (event.type == SDL_KEYDOWN))
				ct->choose_inter = (ct->choose_inter + 1) % INTERFACE_NB;
			// SDL_Delay(20);
		}
		key_events(ct, state);
		angle_limit(ct);
		SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
		SDL_RenderClear(ct->rend);
		choose_interface(ct);
		SDL_RenderPresent(ct->rend);
	}
}

void	choose_interface(t_context *ct)
{
	if (ct->choose_inter == MAP)
		draw_2d(ct);
	else if (ct->choose_inter == GAME)
	{
		draw_background(ct);
		draw_wall(ct);
	}
	// if (ct->choose_inter == MENU)
	// {
	// 	print_menu(ct);
	// }
}
void	angle_limit(t_context *ct)
{
	while (ct->cam.angle >= 360)
		ct->cam.angle = ct->cam.angle - 360;
	while (ct->cam.angle < 0)
		ct->cam.angle = ct->cam.angle + 360;
}

void	key_events(t_context *ct, Uint8 *state)
{
	state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;
	state[SDL_SCANCODE_LEFT] ? ct->cam.angle += 0.15 : 0;
	state[SDL_SCANCODE_RIGHT] ? ct->cam.angle -= 0.15 : 0;
	key_events_movein_2d(ct, state);
	key_events_movein_3d(ct, state);
}

void	key_events_movein_2d(t_context *ct, Uint8 *state)
{
	if ((ct->cam.posi.y - 0.005 > 0)
		&& ct->mpp.map[(int)(ct->cam.posi.y - 0.005)][(int)ct->cam.posi.x] != 1)
		state[SDL_SCANCODE_I] ? ct->cam.posi.y -= 0.005 : 0;
	if ((ct->cam.posi.y + 0.005 < ct->mpp.y)
		&& ct->mpp.map[(int)(ct->cam.posi.y + 0.005)][(int)ct->cam.posi.x] != 1)
		state[SDL_SCANCODE_K] ? ct->cam.posi.y += 0.005 : 0;
	if ((ct->cam.posi.x - 0.005 > 0)
		&& ct->mpp.map[(int)ct->cam.posi.y][(int)(ct->cam.posi.x - 0.005)] != 1)
		state[SDL_SCANCODE_J] ? ct->cam.posi.x -= 0.005 : 0;
	if ((ct->cam.posi.x + 0.005 < ct->mpp.x)
		&& ct->mpp.map[(int)ct->cam.posi.y][(int)(ct->cam.posi.x + 0.005)] != 1)
		state[SDL_SCANCODE_L] ? ct->cam.posi.x += 0.005 : 0;
}

void	key_events_movein_3d(t_context *ct, Uint8 *state)
{
	float	d;
	float	dx;
	float	dy;

	d = 0.005;
	dy = d * sin(convert_degree_to_radian(ct->cam.angle));
	dx = d * cos(convert_degree_to_radian(ct->cam.angle));
	if ((ct->cam.posi.y - dy > 0) && (ct->cam.posi.y - dy < ct->mpp.y)
		&& (ct->cam.posi.x + dx < ct->mpp.x) && (ct->cam.posi.x + dx > 0)
		&& ct->mpp.map[(int)(ct->cam.posi.y - dy)][(int)(ct->cam.posi.x + dx)] != 1)
	{
		if (state[SDL_SCANCODE_UP])
		{
			ct->cam.posi.y -= dy;
			ct->cam.posi.x += dx;
		}
	}
	if ((ct->cam.posi.y + dy < ct->mpp.y) && (ct->cam.posi.y + dy > 0) && (ct->cam.posi.x - dx > 0) && (ct->cam.posi.x - dx < ct->mpp.x)
		&& ct->mpp.map[(int)(ct->cam.posi.y + dy)][(int)(ct->cam.posi.x - dx)] != 1)
	{
		if (state[SDL_SCANCODE_DOWN])
		{
			ct->cam.posi.y += dy;
			ct->cam.posi.x -= dx;
		}
	}
}
