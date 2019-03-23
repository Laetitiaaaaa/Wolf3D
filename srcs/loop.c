/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/21 19:32:32 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loop(t_context *ct)
{
	Uint8	*state;

	while (TRUE)
	{
		SDL_PollEvent(ct->ev);
		state = (Uint8*)SDL_GetKeyboardState(NULL);
		key_events(ct, state);
		SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
		SDL_RenderClear(ct->rend);
		choose_interface(ct);

		key_events(ct);
		if (state[SDL_SCANCODE_C])
		{
			ct->choose_inter = MAP;
		}
		if (state[SDL_SCANCODE_V])
		{
			ct->choose_inter = GAME;
		}


		SDL_RenderPresent(ct->rend);
	}
}

void	choose_interface(t_context *ct)
{

	if (ct->choose_inter == MAP)
	{
		draw_2d(ct);
	}
	if (ct->choose_inter == GAME)
	{
		draw_background(ct);
		draw_wall(ct);
	}

}



void	key_events(t_context *ct, Uint8 *state)
{


	state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;
	state[SDL_SCANCODE_A] ? ct->cam.angle += 0.1 : 0;
	state[SDL_SCANCODE_S] ? ct->cam.angle -= 0.1 : 0;
	if ((ct->cam.cam_position.y - 0.005 > 0)
		&& ct->mpp.map[(int)(ct->cam.cam_position.y - 0.005)][(int)ct->cam.cam_position.x] != 1)
		state[SDL_SCANCODE_UP] ? ct->cam.cam_position.y -= 0.005 : 0;
	if ((ct->cam.cam_position.y + 0.005 < ct->mpp.y)
		&& ct->mpp.map[(int)(ct->cam.cam_position.y + 0.005)][(int)ct->cam.cam_position.x] != 1)
		state[SDL_SCANCODE_DOWN] ? ct->cam.cam_position.y += 0.005 : 0;
	if ((ct->cam.cam_position.x - 0.005 > 0)
		&& ct->mpp.map[(int)ct->cam.cam_position.y][(int)(ct->cam.cam_position.x - 0.005)]!= 1)
		state[SDL_SCANCODE_LEFT] ? ct->cam.cam_position.x -= 0.005 : 0;
	if ((ct->cam.cam_position.x + 0.005 < ct->mpp.x)
		&& ct->mpp.map[(int)ct->cam.cam_position.y][(int)(ct->cam.cam_position.x + 0.005)]!= 1)
		state[SDL_SCANCODE_RIGHT] ? ct->cam.cam_position.x += 0.005 : 0;
}

