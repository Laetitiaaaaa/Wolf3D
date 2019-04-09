/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:58:28 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 16:12:21 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Texture		*init_texture(char *path, t_context *ct)
{
	SDL_Texture		*texture;
	SDL_Surface		*surface;

	texture = NULL;
	if (!(surface = SDL_LoadBMP(path)))
		quit("wrong path\n", ct);
	if (!(texture = SDL_CreateTextureFromSurface(ct->rend, surface)))
		quit("texturefromsurface failed\n", ct);
	SDL_FreeSurface(surface);
	return (texture);
}

void			init_sdl(t_context *ct)
{
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? quit("Initiation failed", ct) : 0;
	if (TTF_Init() == -1)
		quit("TTF_Init() failed", ct);
	IMG_Init(IMG_INIT_PNG);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,
		MIX_DEFAULT_CHANNELS, 1024) == -1)
		quit("initialisation SDL_Mixer failed", ct);
	ct->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, ct->xwin, ct->ywin, SDL_WINDOW_SHOWN);
	if (ct->window == NULL)
		quit("window create failed", ct);
	ct->rend = SDL_CreateRenderer(ct->window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture		*init_texture_png(char *path, t_context *ct)
{
	SDL_Texture		*texture;
	SDL_Surface		*surface;

	texture = NULL;
	surface = IMG_Load(path);
	if (surface == NULL)
		quit("wrong path for IMG_Load\n", ct);
	if (!(texture = SDL_CreateTextureFromSurface(ct->rend, surface)))
		quit("texturefromsurface failed\n", ct);
	SDL_FreeSurface(surface);
	return (texture);
}

int				init(t_context *ct, const char *argv)
{
	ft_bzero(ct, sizeof(*ct));
	load_map(ct, argv);
	init_valeur(ct);
	init_sdl(ct);
	load_music(ct);
	load_font(ct);
	load_texture_backgr(ct);
	load_texture_obj(ct);
	load_texture_wall(ct);
	return (0);
}
