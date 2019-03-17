/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 16:30:47 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loop(t_context *ct)
{
	Uint8		*state;

	while (TRUE)
	{
		SDL_PollEvent(ct->ev);
		state = (Uint8*)SDL_GetKeyboardState(NULL);
		state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;

//----------------jie
		draw_2d(ct);
		//draw_background(ct);

		//jie-------
//----------------laeti

		//----------------laeti-------
		SDL_RenderPresent(ct->rend);
	}
}



void		draw_2d(t_context *ct)
{
	SDL_SetRenderDrawColor(ct->rend, 0, 0, 0,  SDL_ALPHA_OPAQUE);
	SDL_RenderClear(ct->rend);
	draw_cubes(ct);
	draw_camera(ct);
//	draw_ray(ct);

}

void	draw_ray(t_context *ct)
{
	SDL_Point    	pix_cam;
	SDL_Point    	pix_wall;
	t_floatpoint	wall_position;

	pix_cam = convert_plan_to_pixel(ct->cam.cam_position.x, ct->cam.cam_position.y, ct);
	wall_position = dda(ct);
	if (wall_position.x != NO_WALL)
	{
		pix_wall = convert_plan_to_pixel(wall_position.x, wall_position.y, ct);
		SDL_SetRenderDrawColor(ct->rend, 226, 83, 83, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(ct->rend, pix_cam.x, pix_cam.y, pix_wall.x, pix_wall.y);
	}

}

void	draw_camera(t_context *ct)
{
	SDL_Point    	pixel;

	pixel = convert_plan_to_pixel(ct->cam.cam_position.x, ct->cam.cam_position.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 89, 224, 192, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
}


void	draw_cubes(t_context *ct)
{
	SDL_Rect		*rects;
	SDL_Rect		rec;
	int				count;
	SDL_Point		pixel;

	count = ct->mpp.x * ct->mpp.y;
	rects= (SDL_Rect*)malloc(sizeof(SDL_Rect) * count);  //remember to free later

	int	i = 0;
	int	j = 0;
	while (j < ct->mpp.y)
	{
		while (i < ct->mpp.x)
		{
			pixel = convert_plan_to_pixel((float)i, (float)j, ct);
			if (ct->mpp.map[j][i] == 1)
			{
				rec.x = pixel.x;
				rec.y = pixel.y;
				rec.w = XWIN / ct->mpp.x;
				rec.h = YWIN / ct->mpp.y;
				SDL_SetRenderDrawColor(ct->rend, 31, 47, 73, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(ct->rend, &rec);
			}
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
	SDL_RenderDrawRects(ct->rend, rects, count);
}