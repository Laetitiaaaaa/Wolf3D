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

void	free_lst_sp(t_sp_lst *lst)
{
	t_sp_lst *after;

	while (lst != NULL)
	{
		after = lst->next;
		free(lst);
		lst = after;
	}
}

void				quit_nothing_to_free(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void				quit(char *msg, t_context *ct)
{
	ft_putendl(msg);
	ct->mpp.map != NULL ? free_map(ct) : 0;
	ct->window != NULL ? SDL_DestroyWindow(ct->window) : 0;
	ct->rend != NULL ?	SDL_DestroyRenderer(ct->rend) : 0;
	if (ct->lst != NULL)
	{
		free_lst_sp(ct->lst);
		ct->lst = NULL;
	}
	SDL_Quit();
	exit(0);
}

