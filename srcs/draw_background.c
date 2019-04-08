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

void		draw_ground(t_context *ct)
{
	SDL_Rect dst_ground;

	dst_ground =  define_rect(0, ct->ywin / 2, ct->xwin, ct->ywin / 2);
	SDL_RenderCopy(ct->rend, ct->tex.ground, NULL, &dst_ground);
}

void		draw_background(t_context *ct)
{
	SDL_Rect	dst_sky;
	SDL_Rect	src_sky;

	dst_sky = define_rect(0, 0, ct->xwin, ct->ywin / 2);
	draw_ground(ct);
	src_sky.x = (X_SKY - X_CUT_SKY) - ((X_SKY - X_CUT_SKY)
		* ct->cam.angle / 360);
	src_sky.y = 0;
	src_sky.w = X_CUT_SKY;
	src_sky.h = Y_SKY;
	SDL_RenderCopy(ct->rend, ct->tex.sky, &src_sky, &dst_sky);
}
