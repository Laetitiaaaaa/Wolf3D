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

void	draw_sprite_in_2d(t_context *ct)
{
	SDL_Rect		rec_sp;
	SDL_Point		pixel;

	pixel = convert_plan_to_pixel(ct->sp_posi.x, ct->sp_posi.y, ct);
	rec_sp.x = pixel.x;
	rec_sp.y = pixel.y;
	rec_sp.w = (XWIN / ct->mpp.x) - 20;
	rec_sp.h = (YWIN / ct->mpp.y) - 20;
	SDL_SetRenderDrawColor(ct->rend, 134, 244, 66, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ct->rend, &rec_sp);
	ct->sp_visible = FALSE;
}

// void	draw_sprite_in_3d(t_context *ct)
// {
// 	float	distance;
// 	int		sp_height;
// 	SDL_Rect	rect;

// 	distance = sqrt(pow(ct->sp_posi.x - ct->cam.posi.x, 2)	+ pow(sp_posi.y - ct->cam.posi.y, 2));
// 	sp_height = convert_mapsi_to_screendis(distance, ct);

// 	rect.w = sp_height;
// 	rect.h = sp_height;
// 	SDL_SetRenderDrawColor(ct->rend, 211, 77 , 14, SDL_ALPHA_OPAQUE);
// 	SDL_RenderFillRect(ct->rend, &rect);
// }
