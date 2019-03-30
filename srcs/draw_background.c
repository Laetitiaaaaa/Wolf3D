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



	// printf("%f\n", ct->cam.angle );
	src_sky.x = (X_SKY - X_CUT_SKY) - ((X_SKY - X_CUT_SKY)/ 360 ) * ct->cam.angle;
	if (src_sky.x < 0)
		src_sky.x += (X_SKY - X_CUT_SKY) ;
	if (src_sky.x > (X_SKY - X_CUT_SKY))
		src_sky.x = 0;


	// printf("src.x :%d   angle:%f\n", src_sky.x, ct->cam.angle);
	src_sky.y = 0;
	src_sky.w = X_CUT_SKY;
	src_sky.h = Y_SKY;
	SDL_RenderCopy(ct->rend, ct->tex_sky, &src_sky, &dst_sky);

}
