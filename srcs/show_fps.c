/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_fps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:03:40 by jleblond          #+#    #+#             */
/*   Updated: 2019/04/08 18:03:44 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	show_fps(t_context *ct)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	char			*s;
	SDL_Rect		dst;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = SDL_ALPHA_OPAQUE;
	s = ft_itoa(ct->fps);
	surface = TTF_RenderText_Solid(ct->font, s, color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	SDL_FreeSurface(surface);
	dst = define_rect(500, 20, 40, 40);
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
	free(s);
	s = NULL;
	SDL_DestroyTexture(texture);
}
