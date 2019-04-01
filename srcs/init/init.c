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
	ct->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, XWIN, YWIN, SDL_WINDOW_SHOWN);
	if (ct->window == NULL)
		quit("window create failed", ct);
	ct->rend = SDL_CreateRenderer(ct->window, -1, SDL_RENDERER_ACCELERATED);
	load_texture_wall(ct);
}

void	load_texture_wall(t_context *ct)
{
	ct->wall.motif_red = init_texture("./mariowallred.bmp", ct);
	ct->wall.motif_yellow = init_texture("./mariowallyellow.bmp", ct);
	ct->wall.motif_green = init_texture("./mariowallgreen.bmp", ct);
	ct->wall.motif_blue = init_texture("./mariowallblue.bmp", ct);
}

void	load_texture_backgr(t_context *ct)
{
	SDL_Surface	*tmp;

	tmp = SDL_LoadBMP("./srcs/init/Floor.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	ct->tex_ground = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (ct->tex_ground == NULL)
		quit("Error SDL_CreateTextureFromSurface from function load_texture()", ct);
	SDL_FreeSurface(tmp);
	tmp = SDL_LoadBMP("./srcs/init/Sky.bmp");
	if (tmp == NULL)
		quit("Error SDL_LoadBMP", ct);
	ct->tex_sky = SDL_CreateTextureFromSurface(ct->rend, tmp);
	if (ct->tex_sky == NULL)
		quit("Error SDL_CreateTextureFromSurface from function load_texture()", ct);
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

	return (0);
}
