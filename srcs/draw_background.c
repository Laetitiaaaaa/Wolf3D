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
	SDL_Rect dst_ground = {0, YWIN / 2, XWIN, YWIN / 2};
	SDL_RenderCopy(ct->rend, ct->tex_ground, NULL, &dst_ground);
}

void		draw_background(t_context *ct)
{
	SDL_Rect dst_sky = {0, 0, XWIN, YWIN / 2};
	SDL_Rect src_sky;

	draw_ground(ct);
	src_sky.x = (int)(1400.0 -  1400.0 * ct->cam.angle / 360.0);
	src_sky.y = 0;
	src_sky.w = X_CUT_SKY;
	src_sky.h = Y_SKY;
	SDL_RenderCopy(ct->rend, ct->tex_sky, &src_sky, &dst_sky);
}
