/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/18 14:54:16 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loop(t_context *ct)
{

	//print_menu(ct);
	while (TRUE)
	{
		SDL_PollEvent(ct->ev);

//		SDL_RenderCopy(ct->rend, ct->texture, NULL, NULL);
		key_events(ct);

		draw_2d(ct);
		//draw_background(ct);


		SDL_RenderPresent(ct->rend);
	}
}



void	key_events(t_context *ct)
{
	Uint8	*state;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;
	state[SDL_SCANCODE_A] ? ct->cam.angle += 0.2 : 0;
	state[SDL_SCANCODE_S] ? ct->cam.angle -= 0.2 : 0;
	if (ct->cam.cam_position.y - 0.05 > 0)
		state[SDL_SCANCODE_UP] ? ct->cam.cam_position.y -= 0.05 : 0;
	if (ct->cam.cam_position.y + 0.05 < ct->mpp.y)
		state[SDL_SCANCODE_DOWN] ? ct->cam.cam_position.y += 0.05 : 0;
	if (ct->cam.cam_position.x - 0.05 > 0)
		state[SDL_SCANCODE_LEFT] ? ct->cam.cam_position.x -= 0.05 : 0;
	if (ct->cam.cam_position.x + 0.05 < ct->mpp.x)
		state[SDL_SCANCODE_RIGHT] ? ct->cam.cam_position.x += 0.05 : 0;
}
