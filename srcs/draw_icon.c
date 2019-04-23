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

void	draw_fireworks(t_context *ct)
{
	unsigned int	time;
	unsigned int	curr;
	SDL_Rect		dst;

	dst = define_rect(0, 0, ct->xwin, ct->ywin);
	time = SDL_GetTicks();
	curr = time % (FIREWORKS_FRAMES * FIREWORKS_FRAME_TIME);
	SDL_RenderCopy(ct->rend, ct->tex.fireworks[curr / FIREWORKS_FRAME_TIME],
		NULL, &dst);
}

void	sub_draw_text(t_context *ct, t_point posi, SDL_Texture *texture)
{
	int				tex_width;
	int				tex_height;
	SDL_Rect		dst;

	tex_width = 0;
	tex_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &tex_width, &tex_height);
	dst = define_rect(posi.x, posi.y, tex_width, tex_height);
	SDL_RenderCopy(ct->rend, texture, NULL, &dst);
}

void	draw_text(t_context *ct, char *s, t_point posi)
{
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	color.r = 165;
	color.g = 4;
	color.b = 13;
	color.a = SDL_ALPHA_OPAQUE;
	surface = TTF_RenderText_Solid(ct->font, s, color);
	if (surface == NULL)
		quit("TTF_RenderText_Solid()failed", ct);
	texture = SDL_CreateTextureFromSurface(ct->rend, surface);
	if (texture == NULL)
		quit("SDL_CreateTextureFromSurface()failed", ct);
	SDL_FreeSurface(surface);
	sub_draw_text(ct, posi, texture);
	SDL_DestroyTexture(texture);
}

void	draw_icon(t_context *ct)
{
	SDL_Rect	dst_mushroom;
	SDL_Rect	dst_key;
	t_point		posi;
	char		*s;

	posi.x = 80;
	posi.y = 20;
	s = ft_itoa(ct->sp.mushroom_nb);
	draw_text(ct, s, posi);
	free(s);
	s = NULL;
	posi.y = 80;
	s = ft_itoa(ct->sp.key_nb);
	draw_text(ct, s, posi);
	free(s);
	s = NULL;
	dst_mushroom = define_rect(10, 10, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.mushroom, NULL, &dst_mushroom);
	dst_key = define_rect(10, 70, 50, 50);
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst_key);
}
