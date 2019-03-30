/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:55:48 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/28 16:56:03 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				quit_map(char *msg, t_context *ct)
{
	int		i;

	i = 0;
	while (i < ct->mpp.y)
	{
		free(ct->mpp.map[i]);
		i++;
	}
	free(ct->mpp.map);
	ft_putendl(msg);
	exit(0);
}

void				quit_without_malloc(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void	quit_sdl(char *msg, t_context *ct)
{
	ft_putendl(msg);
	(void)ct;
	//codes to add :free the structure and all its contents here
	SDL_DestroyRenderer(ct->rend);
	SDL_DestroyWindow(ct->window);
	SDL_Quit();
	exit(0);
}

