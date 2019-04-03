/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:00:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/04/03 11:00:20 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		hit_sprite(t_context *ct, SDL_Point to_int)
{

	int				id;
	t_floatpoint	posi;
	int 			visible;

	ct->at_least_one_sprite = TRUE;
	visible = TRUE;
	posi.x = (float)to_int.x + (CUBESIZE / 2.0);
	posi.y = (float)to_int.y + (CUBESIZE / 2.0);
	id = ct->mpp.map[to_int.y][to_int.x];
	if (lst_new_sprite_check(ct->lst, id) == TRUE)
		ct->lst = lst_fill(ct->lst, id, posi, visible);
}


t_sp_lst	*lst_fill(t_sp_lst *lst, int id, t_floatpoint posi, int visible)
{
	t_sp_lst	*current;

	current = lst;
	if (current == NULL)
	{
		lst = (t_sp_lst*)malloc(sizeof(t_sp_lst));
		current = lst;
	}
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = (t_sp_lst*)malloc(sizeof(t_sp_lst));
		current = current->next;
	}
	current->posi = posi;
	current->visible = visible;
	current->id = id;
	current->next = NULL;
	return (lst);
}

int		lst_new_sprite_check(t_sp_lst *lst, int id)
{
	int			new_sprite;

	if (lst == NULL)
		return (new_sprite = TRUE);
	while (lst != NULL)
	{
		if (lst->id == id)
			return(new_sprite = FALSE);
		lst = lst->next;
	}
	return (new_sprite = TRUE);
}