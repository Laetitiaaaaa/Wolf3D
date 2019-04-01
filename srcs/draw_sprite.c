/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:29:52 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/31 16:29:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sprite_visible(t_context *ct, SDL_Point to_int, float angle)
{
	ct->sp_visible = TRUE;
	if (angle < ct->sp_angle_min)
	{
		ct->sp_angle_min = angle;
	}
	if (angle > ct->sp_angle_max)
	{
		ct->sp_angle_max = angle;
	}
	ct->sp_posi.x = (float)to_int.x + 0.5;
	ct->sp_posi.y = (float)to_int.y + 0.5;

}

int		get_xpixel_based_on_angle(t_context *ct, float angle)
{
	float	angle_max;
	float	delta_angle;
	int		x_pixel;

	angle_max = ct->cam.angle + 30.0;
	angle_max = angle_limit(angle_max);
	angle = angle_limit(angle);
	if (angle_max - angle >= 0)
		delta_angle = (angle_max - angle);
	if (angle_max - angle < 0)
		delta_angle = angle_max + 360.0 - angle;
	x_pixel = (int)(XWIN * delta_angle / 60.0);
	return (x_pixel);
}


void	draw_sprite_in_2d(t_context *ct)
{
	SDL_Point		pixel;

	pixel = convert_plan_to_pixel(ct->sp_posi.x, ct->sp_posi.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 134, 244, 66, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x - 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x + 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y - 1);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y + 1);
	ct->sp_visible = FALSE;
}

void	draw_sprite_in_3d(t_context *ct)
{
	float	distance;
	int		sp_height;
	SDL_Rect	dst;

	distance = sqrt(pow(ct->sp_posi.x - ct->cam.posi.x, 2)	+ pow(ct->sp_posi.y - ct->cam.posi.y, 2));
	sp_height = convert_mapdis_to_screendis(distance, ct);
	if ((ct->sp_angle_max - ct->sp_angle_min) <= 60 )
		ct->sp_angle = (ct->sp_angle_max + ct->sp_angle_min) / 2;
	else
	{
		ct->sp_angle = (ct->sp_angle_max - 360.0 + ct->sp_angle_min) / 2;
		ct->sp_angle = angle_limit(ct->sp_angle);
	}
	// printf("sp_angle cam.angle(%f, %f)\n", ct->sp_angle, ct->cam.angle );
	// printf("max_angle min.angle(%f, %f)\n", ct->sp_angle_max, ct->sp_angle_min );

	dst.x = get_xpixel_based_on_angle(ct, ct->sp_angle);
	// printf("pix%d\n", dst.x);
	dst.y = YWIN / 2 ;
	dst.w = sp_height;
	dst.h = sp_height;
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst);
	ct->sp_visible = FALSE;
}
