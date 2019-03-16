/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:11:24 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/16 13:11:26 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		dda(t_context *ct)
{
	ct->cam.angle = 0.5235987755983; // angle is 30 degree

	float	dx = 0.1;
	float 	dy = dx * tan(ct->cam.angle);
	int		a = 0;
	int		b = 0;

	printf("dx dy(%f, %f)", dx, dy);

	ct->cam.cam_position.x = 2.5;
	ct->cam.cam_position.y = 4.5;
	float	i = ct->cam.cam_position.x;
	float	j = ct->cam.cam_position.y;
	while (ct->mpp.map[b][a] == 0)
	{
		i = i + dx;
		j = j - dy;
		a = (int)i;
		b = (int)j;
		printf("wall valeur:%d\n", ct->mpp.map[b][a]);
		if (i > 5 || i< 0 || j < 0 || j > 5 )
		{
			printf("There is no wall in this direction\n");
			return ;
		}
	}
	printf("wall found, wall position is (%f, %f)", i, j);
}
