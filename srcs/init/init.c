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

SDL_Texture 	*init_texture(char *path, t_context *ct)
{
	SDL_Texture 	*texture;
	SDL_Surface 	*surface;

	texture = NULL;
	if (!(surface = SDL_LoadBMP(path)))
		quit("wrong path\n", ct);
	if (!(texture = SDL_CreateTextureFromSurface(ct->rend, surface)))
		quit("texturefromsurface failed\n", ct);
	SDL_FreeSurface(surface);
	return (texture);
}

void	init_sdl(t_context *ct)
{
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? quit("Initiation failed", ct) : 0;
	if(TTF_Init() == -1)
		quit("TTF_Init() failed", ct);
	IMG_Init(IMG_INIT_PNG);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		quit("initialisation SDL_Mixer failed", ct);
	ct->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ct->xwin, ct->ywin, SDL_WINDOW_SHOWN);
	if (ct->window == NULL)
		quit("window create failed", ct);
	ct->rend = SDL_CreateRenderer(ct->window, -1, SDL_RENDERER_ACCELERATED);
}

void	load_texture_wall(t_context *ct)
{
	ct->wall.motif_red = init_texture("./images/blocgris.bmp", ct);
	ct->wall.motif_yellow = init_texture("./images/murgris.bmp", ct);
	ct->wall.motif_green = init_texture("./images/bloc.bmp", ct);
	ct->wall.motif_blue = init_texture("./images/murroux.bmp", ct);
}

SDL_Texture 	*init_texture_png(char *path, t_context *ct)
{
	SDL_Texture 	*texture;
	SDL_Surface 	*surface;

	texture = NULL;
	surface = IMG_Load(path);
	if (surface == NULL)
		quit("wrong path for IMG_Load\n", ct);
	if (!(texture = SDL_CreateTextureFromSurface(ct->rend, surface)))
		quit("texturefromsurface failed\n", ct);
	SDL_FreeSurface(surface);
	return (texture);
}

void	load_texture_backgr(t_context *ct)
{
	ct->tex.ground = init_texture("./images/Floor.bmp", ct);
	ct->tex.sky = init_texture("./images/Sky.bmp", ct);
	ct->tex.fireworks[0] = init_texture_png("./images/Fireworks3.png", ct);
	ct->tex.fireworks[1] = init_texture_png("./images/Fireworks4.png", ct);
	ct->tex.fireworks[2] = init_texture_png("./images/Fireworks5.png", ct);
	ct->tex.fireworks[3] = init_texture_png("./images/Fireworks6.png", ct);
	ct->tex.fireworks[4] = init_texture_png("./images/Fireworks7.png", ct);
	ct->tex.fireworks[5] = init_texture_png("./images/Fireworks8.png", ct);
	ct->tex.fireworks[6] = init_texture_png("./images/Fireworks9.png", ct);
	ct->tex.fireworks[7] = init_texture_png("./images/Fireworks10.png", ct);
	ct->tex.fireworks[8] = init_texture_png("./images/Fireworks11.png", ct);
	ct->tex.fireworks[9] = init_texture_png("./images/Fireworks12.png", ct);
}

void	load_texture_obj(t_context *ct)
{
	ct->tex.key = init_texture_png("./images/Key.png", ct);
	ct->tex.mushroom = init_texture_png("./images/Mushroom.png", ct);
	ct->tex.tuyau = init_texture_png("./images/tuyau.png", ct);
}

void	load_font(t_context *ct)
{
	ct->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 35);
	if (ct->font == NULL)
		quit("TTF_OpenFont()failed", ct);
}


void	load_music(t_context *ct)
{
	ct->music = Mix_LoadMUS("./images/mario.wav");
	ct->chunk = Mix_LoadWAV("./images/sonchampi.wav");
}

int		init(t_context *ct, const char *argv)
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
