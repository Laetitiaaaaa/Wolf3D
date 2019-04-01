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


// error information for maps
void	error_info(int x)
{
	if (x == -2)
		ft_putendl("map file should not be empty");
	if (x == -3)
		ft_putendl("content of map file is not right");
	if (x == -1)
		ft_putendl("error");
	if (x == -4)
		ft_putendl("error:the LENGTH OF EACH LINE SHOULD BE THE SAMe");
}


SDL_Texture 	*init_texture(char *path, t_context *ct)
{
	SDL_Texture 	*texture;

	texture = NULL;
	if (!(ct->surface = SDL_LoadBMP(path)))
		quit("can't find mariowallred.bmp\n", ct);
	if (!(texture = SDL_CreateTextureFromSurface(ct->rend, ct->surface)))
		quit("texturefromsurface failed\n", ct);
	SDL_FreeSurface(ct->surface);
	return (texture);
}

void	init_sdl(t_context *ct)
{
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? quit("Initiation failed", ct) : 0;
	ct->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, XWIN, YWIN, SDL_WINDOW_SHOWN);
	if (ct->window == NULL)
		quit("window create failed", ct);
	ct->rend = SDL_CreateRenderer(ct->window, -1, SDL_RENDERER_ACCELERATED);
	ct->wall.motif_red = init_texture("./mariowallred.bmp", ct);
	ct->wall.motif_yellow = init_texture("./mariowallyellow.bmp", ct);
	ct->wall.motif_green = init_texture("./mariowallgreen.bmp", ct);
	ct->wall.motif_blue = init_texture("./mariowallblue.bmp", ct);
}

int		init(t_context *ct, const char *argv)
{
	int		ret;

	ret = load_map(ct, argv);
	if (ret == -1)
	{
		quit("error", ct);
		return (0);
	}
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

	return (0);
}
