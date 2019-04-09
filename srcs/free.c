/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:20:47 by llejeune          #+#    #+#             */
/*   Updated: 2019/04/09 11:20:49 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				free_map(t_context *ct)
{
	int		i;

	i = 0;
	while ((i < ct->mpp.y) && (ct->mpp.map[i] != NULL))
	{
		free(ct->mpp.map[i]);
		i++;
	}
	free(ct->mpp.map);
}

void				free_lst_sp(t_sp_lst *lst)
{
	t_sp_lst *after;

	while (lst != NULL)
	{
		after = lst->next;
		free(lst);
		lst = after;
	}
}

void				free_texture(t_context *ct)
{
	ct->wall.motif_red != NULL ? SDL_DestroyTexture(ct->wall.motif_red) : 0;
	ct->wall.motif_yellow != NULL ?
	SDL_DestroyTexture(ct->wall.motif_yellow) : 0;
	ct->wall.motif_green != NULL ? SDL_DestroyTexture(ct->wall.motif_green) : 0;
	ct->wall.motif_blue != NULL ? SDL_DestroyTexture(ct->wall.motif_blue) : 0;
	ct->tex.ground != NULL ? SDL_DestroyTexture(ct->tex.ground) : 0;
	ct->tex.sky != NULL ? SDL_DestroyTexture(ct->tex.sky) : 0;
	ct->tex.key != NULL ? SDL_DestroyTexture(ct->tex.key) : 0;
	ct->tex.mushroom != NULL ? SDL_DestroyTexture(ct->tex.mushroom) : 0;
	ct->tex.tuyau != NULL ? SDL_DestroyTexture(ct->tex.tuyau) : 0;
}

void				free_sound(t_context *ct)
{
	ct->chunk_menu != NULL ? Mix_FreeChunk(ct->chunk_menu) : 0;
	ct->chunky != NULL ? Mix_FreeChunk(ct->chunky) : 0;
	ct->chunk != NULL ? Mix_FreeChunk(ct->chunk) : 0;
	ct->music != NULL ? Mix_FreeMusic(ct->music) : 0;
}
