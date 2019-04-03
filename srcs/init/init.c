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

void	init_struct(t_context *ct)
{
	ct->mpp.map = NULL;
	ct->window = NULL;
	ct->sp_angle_min = 360.0;
	ct->sp_angle_max = 0.0;
	ct->xwin = XWIN;
	ct->ywin = YWIN;
}


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
	IMG_Init(IMG_INIT_PNG);
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

void	load_texture_backgr(t_context *ct)
{
	SDL_Surface	*tmp;

	tmp = SDL_LoadBMP("./images/Floor.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	ct->tex.ground = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (ct->tex.ground == NULL)
		quit("Error SDL_CreateTextureFromSurface from function load_texture()", ct);
	SDL_FreeSurface(tmp);
	tmp = SDL_LoadBMP("./images/Sky.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	ct->tex.sky = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (ct->tex.sky == NULL)
		quit("Error SDL_CreateTextureFromSurface from function load_texture()", ct);
	SDL_FreeSurface(tmp);
}

void	load_texture_obj(t_context *ct)
{
	SDL_Surface	*tmp;

	tmp =  IMG_Load("./images/Key.png");
	if (tmp == NULL)
		quit("Error IMG_Load Key.png", ct);
	ct->tex.key = SDL_CreateTextureFromSurface(ct->rend, tmp);
 	if (ct->tex.key == NULL)
		quit("Error SDL_CreateTextureFromSurface from function load_texture_obj()", ct);
	SDL_FreeSurface(tmp);
}


int		init(t_context *ct, const char *argv)
{
	init_struct(ct);
	load_map(ct, argv);
/// ---------unleve les commentaires pour affichier le map
	// printf("mppx et mppy(%d, %d)\n", ct->mpp.x, ct->mpp.y);
	// int	i = 0;
	// int	j = 0;
	// while (j < ct->mpp.y)
	// {
	// 	while (i < ct->mpp.x)
	// 	{
	// 		printf("%d", ct->mpp.map[j][i]);
	// 		i++;
	// 	}
	// 	printf("\n");
	// 	i = 0;
	// 	j++;
	// }
// ---------------------------------
	init_event(ct);
	init_sdl(ct);
	load_texture_backgr(ct);
	load_texture_obj(ct);
	load_texture_wall(ct);
	return (0);
}
