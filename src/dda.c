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
	float			distance_hor_wall;
	t_floatpoint 	hor_wall_p;

	distance_ver_wall = NO_WALL;
	distance_hor_wall = NO_WALL;
	ct->cam.angle = 30;
	ct->cam.cam_position.x = 2.5;
	ct->cam.cam_position.y = 4.5;
	ver_wall_p = vertial_wall_position_calcu(ct);
	if (ver_wall_p.x != NO_WALL)
		distance_ver_wall = (((float)ver_wall_p.x) - ct->cam.cam_position.x) / cos(convert_degree_to_radian(ct->cam.angle));
	hor_wall_p = horizontal_wall_position_calcu(ct);
	printf("distance calcu   hori position(%f, %f)\n", hor_wall_p.x, hor_wall_p.y);
	if (hor_wall_p.x != NO_WALL)
		distance_hor_wall = (ct->cam.cam_position.y - (float)hor_wall_p.y) / sin(convert_degree_to_radian(ct->cam.angle));
	printf("distance_hor_wall:%f distance_ver_wall:%f\n", distance_hor_wall, distance_ver_wall);

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
			ret.y = NO_WALL;
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

t_floatpoint		horizontal_wall_position_calcu(t_context *ct)
{
	t_floatpoint	ret;
	t_floatpoint	d = horizontal_first_delta_calcu(ct);

	ret.x = ct->cam.cam_position.x;
	ret.y = ct->cam.cam_position.y;
	int				count = 0;

	int		int_x = (int)ret.x;
	int		int_y = (int)ret.y;

	while (ct->mpp.map[int_y - 1][int_x] == 0)
	{
		if (count == 0)
		{
			ret.x = ret.x + d.x;
			ret.y = ret.y - d.y;
			printf("horizontal first round ret.x ret.y(%f, %f)\n", ret.x, ret.y);
			count++;
		}
		else
		{
			ret.y = ret.y - CUBESIZE;
			ret.x = ret.x + CUBESIZE / tan(convert_degree_to_radian(ct->cam.angle));
			printf("horizontal second and later round ret.x ret.y(%f, %f)\n", ret.x, ret.y);
		}
		int_x = (int)ret.x;
		int_y = (int)ret.y;
		//printf("wall valeur:%d\n", ct->mpp.map[int_y][int_ret.x]);
		if (ret.x > CUBESIZE * (ct->mpp.x) || ret.x < 0 || ret.y < 0 || ret.y > CUBESIZE * (ct->mpp.y))
		{
			ret.x = NO_WALL;
			ret.y = NO_WALL;
			printf("horizontal There is no wall in this direction\n");
			return(ret) ;
		}
	}
	return (ret);
	printf("horizontal wall found, wall position is (%f, %f)", ret.x, ret.y);
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