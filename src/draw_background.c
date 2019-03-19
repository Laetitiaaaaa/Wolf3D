/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:54:26 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/16 13:54:27 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_background(t_context *ct)
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
