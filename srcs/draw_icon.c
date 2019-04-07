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

void	draw_text(t_context *ct)
{
	TTF_Font		*font;
	SDL_Color		color = {255, 255, 255,  SDL_ALPHA_OPAQUE};
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25);
	if (font == NULL)
		quit("TTF_OpenFont()failed", ct);
	surface = TTF_RenderText_Solid(font, ft_itoa(ct->sp.mushroom_nb), color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	int	texw = 0;
	int texh = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texw, &texh);
	SDL_Rect dst= {80, 20, texw, texh };
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
	TTF_CloseFont(font);
}

void	draw_icon(t_context *ct)
{
	SDL_Rect dst_mushroom;
	SDL_Rect dst_key;

	dst_mushroom = define_rect(10, 10, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.mushroom, NULL, &dst_mushroom);
	draw_text(ct);
	dst_key = define_rect(10, 200, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst_key);

}