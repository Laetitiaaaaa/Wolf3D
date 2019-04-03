/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:58:49 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/19 15:58:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_cam(t_context *ct)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (j < ct->mpp.y)
	{
		while (i < ct->mpp.x)
		{
			if (ct->mpp.map[j][i] == CAM_CUBE)
			{
				ct->cam.posi.x = (float)i;
				ct->cam.posi.y = (float)j;
				count++;
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (count == 0)
		quit("wrong map: camera postion not defined in map", ct);
	if (count > 1)
		quit("wrong map: there are more than one camera in map", ct);
}

void	init_valeur(t_context *ct)
{
	find_cam(ct);
	ct->cam.angle = 5.0;
	ct->sp.key_nb = 0;
	ct->sp.mushroom_nb = 0;
	ct->full_screen = 1;
	ct->menu.in = PLAY;
	ct->choose_inter = GAME;
	ct->xwin = XWIN;
	ct->ywin = YWIN;
}

void	init_struct(t_context *ct)
{
	ct->mpp.map = NULL;
	ct->window = NULL;
	ct->lst = NULL;
	ct->rend = NULL;
}

