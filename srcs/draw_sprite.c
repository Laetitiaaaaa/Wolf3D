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

void		hit_sprite(t_context *ct, SDL_Point to_int)
{
	ct->sp_visible = TRUE;
	ct->sp_posi.x = (float)to_int.x + 0.5;
	ct->sp_posi.y = (float)to_int.y + 0.5;
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



void		print_sprite(t_context *ct)
{
	SDL_Rect	dst;
	int			sp_height;

	sp_height = convert_mapdis_to_screendis(distance, ct);

	delta_angle = sp_position_angle - ct->cam.angle;
	dst.x = XWIN / 2 - XWIN / 60 * delta_angle;
	dst.y = YWIN / 2 ;
	dst.w = sp_height / 2;
	dst.h = sp_height / 2;
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst);


}
void	draw_sprite_in_3d(t_context *ct)
{
	float		distance;
	float		sp_position_angle;
	float		delta_angle;
	float wall_dis;

	distance = sqrt(pow(ct->sp_posi.x - ct->cam.posi.x, 2)	+ pow(ct->sp_posi.y - ct->cam.posi.y, 2));
	sp_position_angle = convert_rad_to_deg(atan2((ct->sp_posi.y - ct->cam.posi.y) * (-1) , (ct->sp_posi.x - ct->cam.posi.x)));
	sp_position_angle = angle_limit(sp_position_angle);

	wall_dis = dda_return_distance(ct, sp_position_angle);
	if (wall_dis < 0 || wall_dis > distance )
	{

	}


	ct->sp_visible = FALSE;
}
