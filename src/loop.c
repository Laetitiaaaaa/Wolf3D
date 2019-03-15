/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 16:30:47 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loop(t_context *ct)
{
	Uint8		*state;

	while (TRUE)
	{
		SDL_PollEvent(ct->ev);
		state = (Uint8*)SDL_GetKeyboardState(NULL);
		state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;

//----------------jie

		draw_background(ct);
		//jie-------


//----------------laeti


		//----------------laeti-------
		SDL_RenderPresent(ct->rend);


	}
}

void	draw_background(t_context *ct)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	SDL_SetRenderDrawColor(ct->rend, 21, 24, 30, 255);
	while (y < YWIN / 2)
	{
		while (x < XWIN)
		{
			SDL_RenderDrawPoint(ct->rend, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	SDL_SetRenderDrawColor(ct->rend, 95, 99, 107, 255);
	while (y >= YWIN / 2 && y < YWIN)
	{
		while (x < XWIN)
		{
			SDL_RenderDrawPoint(ct->rend, x, y);
			x++;
		}
		x = 0;
		y++;
	}

}