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

void		draw_background(t_context *ct)
{

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
	SDL_Rect dst = {0, YWIN / 2, XWIN - 1, YWIN / 2};

	SDL_Surface	*tmp = NULL;
	SDL_Texture *texture = NULL;
	tmp = SDL_LoadBMP("./srcs/init/Floor.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, tmp);
	SDL_FreeSurface(tmp);
	if (texture == NULL)
		quit("Error SDL_CreateTextureFromSurface", ct);
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
// draw pixel by pixel make it very slow, it will be replaced by texture

	// int		x;
	// int		y;

	// x = 0;
	// y = 0;
	// SDL_SetRenderDrawColor(ct->rend, 21, 24, 30, 255);
	// while (y < YWIN / 2)
	// {
	// 	while (x < XWIN)
	// 	{
	// 		SDL_RenderDrawPoint(ct->rend, x, y);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	// SDL_SetRenderDrawColor(ct->rend, 95, 99, 107, 255);
	// while (y >= YWIN / 2 && y < YWIN)
	// {
	// 	while (x < XWIN)
	// 	{
	// 		SDL_RenderDrawPoint(ct->rend, x, y);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
}
