/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:30:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/21 19:31:50 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_ray(t_context *ct, float angle)
{
	SDL_Point			pix_cam;
	SDL_Point			pix_wall;
	t_floatpoint		wall_p;

	wall_p = dda_return_posi(ct, angle);
	if (wall_p.x == NO_WALL)
		return ;
	pix_cam = convert_plan_to_pixel(ct->cam.posi.x, ct->cam.posi.y, ct);
	pix_wall = convert_plan_to_pixel(wall_p.x, wall_p.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 226, 83, 83, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ct->rend, pix_cam.x, pix_cam.y, pix_wall.x, pix_wall.y);
}

static void	draw_camera(t_context *ct)
{
	SDL_Point	pixel;

	pixel = convert_plan_to_pixel(ct->cam.posi.x, ct->cam.posi.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 89, 224, 192, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
}

static void	draw_fill_cubes(t_context *ct, SDL_Point pixel)
{
	SDL_Rect		rec;

	rec.x = pixel.x;
	rec.y = pixel.y;
	rec.w = ct->xwin / ct->mpp.x;
	rec.h = ct->ywin / ct->mpp.y;
	SDL_SetRenderDrawColor(ct->rend, 31, 47, 73, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ct->rend, &rec);
}

static void	draw_cubes(t_context *ct)
{
	SDL_Rect		rects[ct->mpp.x * ct->mpp.y];
	SDL_Point		pixel;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < ct->mpp.y)
	{
		while (i < ct->mpp.x)
		{
			pixel = convert_plan_to_pixel((float)i, (float)j, ct);
			ct->mpp.map[j][i] == 1 ? draw_fill_cubes(ct, pixel) : 0;
			rects[j * (ct->mpp.x) + i] = define_rect(pixel.x, pixel.y,
				ct->xwin / ct->mpp.x, ct->ywin / ct->mpp.y);
			i++;
		}
		i = 0;
		j++;
	}
	SDL_SetRenderDrawColor(ct->rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRects(ct->rend, rects, ct->mpp.x * ct->mpp.y);
}

void		draw_2d(t_context *ct)
{
	float angle;

	draw_cubes(ct);
	draw_camera(ct);
	angle = ct->cam.angle + 30;
	while (angle >= (ct->cam.angle - 30.0))
	{
		angle -= (float)ANGLE / (float)ct->xwin;
		draw_ray(ct, angle);
	}
}
