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
	t_floatpoint 	ver_wall_p;
	float			distance_ver_wall;
	t_floatpoint 	hor_wall_position;

	distance_ver_wall = NO_WALL;
	ct->cam.angle = 30;
	ct->cam.cam_position.x = 2.5;
	ct->cam.cam_position.y = 4.5;
	ver_wall_p = vertial_wall_position_calcu(ct);
	if (ver_wall_p.x != NO_WALL)
	{
		distance_ver_wall = (((float)ver_wall_p.x) - ct->cam.cam_position.x) / sin(convert_degree_to_radian(ct->cam.angle));
	}
	horizontal_wall_position_calcu(ct);
}


t_floatpoint		vertical_first_delta_calcu(t_context *ct)
{
	t_floatpoint	d;
	d.x = ((float)(int)(ct->cam.cam_position.x + 1)) - ct->cam.cam_position.x;
	d.y = d.x * tan(convert_degree_to_radian(ct->cam.angle));

	return (d);
}




t_floatpoint			vertial_wall_position_calcu(t_context *ct)
{
	t_floatpoint	ret;
	ret.x = ct->cam.cam_position.x;
	ret.y = ct->cam.cam_position.y;
	t_floatpoint	d = vertical_first_delta_calcu(ct);
	int				count = 0;

	int		int_x = (int)ret.x;
	int		int_y = (int)ret.y;

	while (ct->mpp.map[int_y][int_x] == 0)
	{
		if (count == 0)
		{
			ret.x = ret.x + d.x;
			ret.y = ret.y - d.y;
			count++;
		}
		else
		{
			ret.x = ret.x + CUBESIZE;
			ret.y = ret.y - CUBESIZE * tan(convert_degree_to_radian(ct->cam.angle));
		}
		int_x = (int)ret.x;
		int_y = (int)ret.y;
		if (ret.x > CUBESIZE * (ct->mpp.x) || ret.x < 0 || ret.y < 0 || ret.y > CUBESIZE * (ct->mpp.y))
		{
			ret.x = NO_WALL;
			return (ret);
		}
	}
	return(ret);

}

t_floatpoint		horizontal_first_delta_calcu(t_context *ct)
{
	t_floatpoint	d2;
	d2.y =  ct->cam.cam_position.y - (float)((int)(ct->cam.cam_position.y));
	d2.x = d2.y / tan(convert_degree_to_radian(ct->cam.angle));
	return (d2);
}

void			horizontal_wall_position_calcu(t_context *ct)
{
	float			x = ct->cam.cam_position.x;
	float			y = ct->cam.cam_position.y;
	t_floatpoint	d = horizontal_first_delta_calcu(ct);
	int				count = 0;

	int		int_x = (int)x;
	int		int_y = (int)y;

	while (ct->mpp.map[int_y - 1][int_x] == 0)
	{
		if (count == 0)
		{
			x = x + d.x;
			y = y - d.y;
			printf("horizontal first round x y(%f, %f)\n", x, y);
			count++;
		}
		else
		{
			y = y - CUBESIZE;
			x = x + CUBESIZE * tan(convert_degree_to_radian(ct->cam.angle));
			printf("horizontal second and later round x y(%f, %f)\n", x, y);
		}
		int_x = (int)x;
		int_y = (int)y;
		//printf("wall valeur:%d\n", ct->mpp.map[int_y][int_x]);
		if (x > CUBESIZE * (ct->mpp.x) || x < 0 || y < 0 || y > CUBESIZE * (ct->mpp.y))
		{
			printf("horizontal There is no wall in this direction\n");
			return ;
		}
	}
	printf("horizontal wall found, wall position is (%f, %f)", x, y);
}


// float		tan_angle_abs(float angle)
// {
// 	double	angle_abs;

// 	angle_abs = tan(convert_degree_to_radian(angle));
// 	if (angle_abs < 0)
// 	{
// 		return (-angle_abs);
// 	}
// 	return(angle_abs);
// }