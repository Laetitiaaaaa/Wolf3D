/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_icon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:50:11 by jleblond          #+#    #+#             */
/*   Updated: 2019/04/07 16:50:12 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"




void	draw_text(t_context *ct, char *s, SDL_Point posi)
{
	SDL_Color		color = {165, 4, 13,  SDL_ALPHA_OPAQUE};
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 35);
	if (font == NULL)
		quit("TTF_OpenFont()failed", ct);
	surface = TTF_RenderText_Solid(font, s, color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	TTF_CloseFont(font);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	int	texw = 0;
	int texh = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texw, &texh);
	SDL_Rect dst= {posi.x, posi.y, texw, texh };
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
}

void	draw_icon(t_context *ct)
{
	SDL_Rect dst_mushroom;
	SDL_Rect dst_key;
	SDL_Point	posi;

	posi.x = 80;
	posi.y = 20;
	draw_text(ct, ft_itoa(ct->sp.mushroom_nb), posi);
	posi.y = 80;
	draw_text(ct, ft_itoa(ct->sp.key_nb), posi);
	dst_mushroom = define_rect(10, 10, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.mushroom, NULL, &dst_mushroom);
	dst_key = define_rect(10, 70, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst_key);
}