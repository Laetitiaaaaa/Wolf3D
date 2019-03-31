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

void		sprite_visible(t_context *ct, SDL_Point to_int)
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

void	draw_sprite_in_3d(t_context *ct, float angle)
{
	// (void)ct;
	// (void)angle;
	float	distance;
	int		sp_height;
	SDL_Rect	rect;

	distance = sqrt(pow(ct->sp_posi.x - ct->cam.posi.x, 2)	+ pow(ct->sp_posi.y - ct->cam.posi.y, 2));
	sp_height = convert_mapdis_to_screendis(distance, ct);

	rect.w = sp_height;
	rect.h = sp_height;
	SDL_SetRenderDrawColor(ct->rend, 211, 77 , 14, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ct->rend, &rect);
	ct->sp_visible = FALSE;
}
