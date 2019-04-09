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

void				quit_nothing_to_free(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void				quit(char *msg, t_context *ct)
{
	ft_putendl(msg);
	free_texture(ct);
	free_sound(ct);
	ct->mpp.map != NULL ? free_map(ct) : 0;
	ct->font != NULL ? TTF_CloseFont(ct->font) : 0;
	if (ct->lst != NULL)
	{
		free_lst_sp(ct->lst);
		ct->lst = NULL;
	}
	ct->rend != NULL ? SDL_DestroyRenderer(ct->rend) : 0;
	ct->window != NULL ? SDL_DestroyWindow(ct->window) : 0;
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	exit(0);
}
