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

void		draw_2d(t_context *ct)
{
	float angle;

	draw_cubes(ct);
	draw_camera(ct);
	draw_ray(ct, ct->cam.angle);
	angle = ct->cam.angle;
	while (angle <= (ct->cam.angle + 30.0))
	{
		angle += 30.0 / (float)(XWIN / 2) ;
		draw_ray(ct, angle);
	}
	angle = ct->cam.angle;
	while (angle >= ct->cam.angle - 30.0)
	{
		angle -= 30.0 / (float)(XWIN / 2);
		draw_ray(ct, angle);
	}

}

void	draw_ray(t_context *ct, float angle)
{
	SDL_Point		pix_cam;
	SDL_Point		pix_wall;
	t_wall			wall_p;

	wall_p = dda(ct, angle);
	if (wall_p.posi.x == NO_WALL)
		return ;
	pix_cam = convert_plan_to_pixel(ct->cam.cam_position.x, ct->cam.cam_position.y, ct);
	pix_wall = convert_plan_to_pixel(wall_p.posi.x, wall_p.posi.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 226, 83, 83, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ct->rend, pix_cam.x, pix_cam.y, pix_wall.x, pix_wall.y);
}

void	draw_camera(t_context *ct)
{
	SDL_Point    	pixel;

	pixel = convert_plan_to_pixel(ct->cam.cam_position.x, ct->cam.cam_position.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 89, 224, 192, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
}

void	draw_fill_cubes(t_context *ct, SDL_Point pixel)
{
	SDL_Rect		rec;

	rec.x = pixel.x;
	rec.y = pixel.y;
	rec.w = XWIN / ct->mpp.x;
	rec.h = YWIN / ct->mpp.y;
	SDL_SetRenderDrawColor(ct->rend, 31, 47, 73, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ct->rend, &rec);
}

void	draw_cubes(t_context *ct)
{
	SDL_Rect		*rects;
	SDL_Point		pixel;
	int				i;
	int				j;

	i = 0;
	j = 0;
	rects= (SDL_Rect*)malloc(sizeof(SDL_Rect) * ct->mpp.x * ct->mpp.y);  //free malloc code not written yet
	if (rects == NULL)
	{
		quit("malloc in function drawcubes failed", ct);
	}
	while (j < ct->mpp.y)
	{
		while (i < ct->mpp.x)
		{
			pixel = convert_plan_to_pixel((float)i, (float)j, ct);
			ct->mpp.map[j][i] == 1 ? draw_fill_cubes(ct, pixel): 0;
			rects[j * (ct->mpp.x) + i].x = pixel.x;
			rects[j * (ct->mpp.x) + i].y = pixel.y;
			rects[j * (ct->mpp.x) + i].w = XWIN / ct->mpp.x;
			rects[j * (ct->mpp.x) + i].h = YWIN / ct->mpp.y;
			i++;
		}
		i = 0;
		j++;
	}
	SDL_SetRenderDrawColor(ct->rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRects(ct->rend, rects, ct->mpp.x * ct->mpp.y);
}
