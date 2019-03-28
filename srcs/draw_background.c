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
	SDL_Surface	*tmp;
	SDL_Rect dst_ground = {0, YWIN / 2, XWIN, YWIN / 2};
	SDL_Texture *textu_ground;

	tmp = NULL;
	textu_ground = NULL;
	tmp = SDL_LoadBMP("./srcs/init/Floor.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	textu_ground = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (textu_ground == NULL)
		quit("Error SDL_CreateTextureFromSurface", ct);
	SDL_FreeSurface(tmp);
	SDL_RenderCopy(ct->rend, textu_ground, NULL, &dst_ground);

}

void		draw_background(t_context *ct)
{
	SDL_Surface	*tmp;
	SDL_Rect dst_sky = {0, 0, XWIN, YWIN / 2};
	SDL_Rect src_sky;
	SDL_Texture *textu_sky;

	// SDL_Rect	*rect1;
	// SDL_Rect	*rect2;

	// rect1 = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	// rect2 = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	// SDL_SetRenderDrawColor(ct->rend, 21, 24, 30, SDL_ALPHA_OPAQUE);
	// rect1->x = 0;
	// rect1->y = 0;
	// rect1->w = XWIN;
	// rect1->h = YWIN / 2;
	// SDL_RenderFillRect(ct->rend, rect1);
	// SDL_SetRenderDrawColor(ct->rend, 95, 99, 107, SDL_ALPHA_OPAQUE);
	// rect2->x = 0;
	// rect2->y = YWIN / 2;
	// rect2->w = XWIN;
	// rect2->h = YWIN / 2;
	// SDL_RenderFillRect(ct->rend, rect2);
	draw_ground(ct);

	tmp = SDL_LoadBMP("./srcs/init/Sky.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	textu_sky = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (textu_sky == NULL)
		quit("Error SDL_CreateTextureFromSurface", ct);
	SDL_FreeSurface(tmp);
	src_sky.x = XIMG_SKY - (int) (((XIMG_SKY - XWIN / XWIN) / 360 ) * ct->cam.angle);
	if (src_sky.x == XIMG_SKY - XWIN )
		src_sky.x = 0;

	// printf("src.x :%d   angle:%f\n", src_sky.x, ct->cam.angle);
	src_sky.y = 0;
	src_sky.w = XWIN;
	src_sky.h = YWIN / 2;
	SDL_RenderCopy(ct->rend, textu_sky, &src_sky, &dst_sky);

}
