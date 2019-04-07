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
	float			distance;

	ct->at_least_one_sprite = TRUE;
	posi.x = (float)to_int.x + (CUBESIZE / 2.0);
	posi.y = (float)to_int.y + (CUBESIZE / 2.0);
	distance = sqrt(pow(posi.x - ct->cam.posi.x, 2) + pow(posi.y - ct->cam.posi.y, 2));
	id = ct->mpp.map[to_int.y][to_int.x];
	if (lst_new_sprite_check(ct->lst, id) == TRUE)
		ct->lst = lst_fill(ct->lst, id, posi, distance);
}


t_sp_lst	*lst_fill(t_sp_lst *lst, int id, t_floatpoint posi, float distance)
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
	current->distance = distance;
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


// void	swap(t_sp_lst *max, t_sp_lst *cmp)
// {



// }

t_sp_lst	*sort_list(t_sp_lst *lst)
{
	t_sp_lst 	*max;
	t_sp_lst	*cmp;
	// t_sp_lst	*test;
	int				id_tmp;
	float			distance_tmp;
	t_floatpoint	posi_tmp;

	max = lst;


	// test = lst;
	// while (test!= NULL)
	// {
	// 	printf("before_testid(%d, %f)\n", test->id, test->distance);
	// 	test = test->next;
	// }



	while (max->next != NULL)
	{
		cmp = max->next;
		while (cmp != NULL)
		{
			if (max->distance < cmp->distance)
			{
				id_tmp = max->id;
				distance_tmp = max->distance;
				posi_tmp.x = max->posi.x;
				posi_tmp.y = max->posi.y;
				max->id = cmp->id;
				max->distance = cmp->distance;
				max->posi.x = cmp->posi.x;
				max->posi.y = cmp->posi.y;
				cmp->id = id_tmp;
				cmp->distance = distance_tmp;
				cmp->posi.x = posi_tmp.x;
				cmp->posi.y = posi_tmp.y;
				printf("%f | %f \n", max->distance, cmp->distance);
			}
			cmp = cmp->next;
		}
		max = max->next;
	}

	max = lst;
	while (max->next != NULL)
	{
		printf("%f\t", max->distance);
		max = max->next;
	}
	printf("%f\t", max->distance);
	printf("\n");

	// test = lst;
	// while (test!= NULL)
	// {
	// 	printf("after_restid(%d, %f)\n", test->id, test->distance);
	// 	test = test->next;
	// }


	return (lst);
}



















