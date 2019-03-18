/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_horizontalwall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:10:42 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/18 18:10:44 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_floatpoint		horizontal_first_delta_calcu(t_context *ct)
{
	t_floatpoint	d;

	if (ct->cam.angle > 90 && ct->cam.angle < 270)
	{
		d.x = ft_float_abs(ct->cam.cam_position.x - (float)(int)(ct->cam.cam_position.x));
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(ct->cam.angle)));
	}
	else if (ct->cam.angle == 90)
	{
		d.x = 0;
		d.y = ct->cam.cam_position.y - (float)(int)(ct->cam.cam_position.y);
	}
	else if (ct->cam.angle == 270)
	{
		d.x = 0;
		d.y = ((float)(int)(ct->cam.cam_position.y + 1)) - ct->cam.cam_position.y;
	}
	else
	{
		d.x = ft_float_abs(((float)(int)(ct->cam.cam_position.x + 1)) - ct->cam.cam_position.x);
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(ct->cam.angle)));
	}
	d.y =  ct->cam.cam_position.y - (float)((int)(ct->cam.cam_position.y));
	d.x = d.y / tan(convert_degree_to_radian(ct->cam.angle));
	return (d);
}

t_floatpoint		horizontal_wall_position_calcu(t_context *ct)
{
	t_floatpoint	detect;
	t_floatpoint	d = horizontal_first_delta_calcu(ct);

	detect.x = ct->cam.cam_position.x;
	detect.y = ct->cam.cam_position.y;
	int				count = 0;

	int		int_x = (int)detect.x;
	int		int_y = (int)detect.y;

	while (ct->mpp.map[int_y - 1][int_x] == 0)  //attention for -1 here
	{
		if (count == 0)
		{
			detect.x = detect.x + d.x;
			detect.y = detect.y - d.y;
		//	printf("horizontal first round detect.x detect.y(%f, %f)\n", detect.x, detect.y);
			count++;
		}
		else
		{
			detect.y = detect.y - CUBESIZE;
			detect.x = detect.x + CUBESIZE / tan(convert_degree_to_radian(ct->cam.angle));
		//	printf("horizontal second and later round detect.x detect.y(%f, %f)\n", detect.x, detect.y);
		}
		int_x = (int)detect.x;
		int_y = (int)detect.y;
		//printf("wall valeur:%d\n", ct->mpp.map[int_y][int_detect.x]);
		if (detect.x > ct->mpp.x || detect.x < 0 || detect.y < 1 || detect.y > ct->mpp.y)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
			printf("horizontal There is no wall in this direction\n");
			return(detect) ;
		}
	}
	return (detect);
	printf("horizontal wall found, wall position is (%f, %f)\n", detect.x, detect.y);
}