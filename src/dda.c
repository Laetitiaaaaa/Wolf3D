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

t_floatpoint		dda(t_context *ct)
{
	t_floatpoint 	posi_ver;
	t_floatpoint 	posi_hor;
	float			distance_ver;
	float			distance_hor;


	ct->cam.cam_position.x = 2.5;
	ct->cam.cam_position.y = 4.5;


	posi_ver = vertial_wall_position_calcu(ct);
	posi_hor = horizontal_wall_position_calcu(ct);
	distance_ver = ft_float_abs((((float)posi_ver.x) - ct->cam.cam_position.x) / cos(convert_degree_to_radian(ct->cam.angle)));
	distance_hor = ft_float_abs((ct->cam.cam_position.y - (float)posi_hor.y) / sin(convert_degree_to_radian(ct->cam.angle)));
	if (posi_ver.x == NO_WALL && posi_hor.x == NO_WALL)
		return (posi_ver);
	else if (posi_ver.x == NO_WALL)
		return (posi_hor);
	else if (posi_hor.x == NO_WALL)
		return (posi_ver);
	else
		return(distance_ver < distance_hor ? posi_ver : posi_hor);
}


t_floatpoint		vertical_first_delta_calcu(t_context *ct)
{
	t_floatpoint	d;

	d.x = ft_float_abs(((float)(int)(ct->cam.cam_position.x + 1)) - ct->cam.cam_position.x);
	d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(ct->cam.angle)));
	return (d);
}

void		set_neg_posi(t_context *ct)
{
	while (ct->cam.angle >= 360)
		ct->cam.angle = ct->cam.angle - 360;
	if ((ct->cam.angle > 0) && (ct->cam.angle < 90))
	{
		ct->cam.neg_posi.x = POSITIVE;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if (ct->cam.angle == 90)
	{
		ct->cam.neg_posi.x = ZERO;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if ((ct->cam.angle > 90) && (ct->cam.angle <= 180))
	{
		ct->cam.neg_posi.x = NEGATIVE;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if ((ct->cam.angle > 180) && (ct->cam.angle < 270))
	{
		ct->cam.neg_posi.x = NEGATIVE;
		ct->cam.neg_posi.y = POSITIVE;
	}
	if (ct->cam.angle == 270)
	{
		ct->cam.neg_posi.x = ZERO;
		ct->cam.neg_posi.y = POSITIVE;
	}
	if ((ct->cam.angle > 270) && (ct->cam.angle < 360))
	{
		ct->cam.neg_posi.x = POSITIVE;
		ct->cam.neg_posi.y = POSITIVE;
	}
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

	set_neg_posi(ct);
	while (ct->mpp.map[int_y][int_x] == 0)
	{
		if (count == 0)
		{
			ret.x = ret.x + d.x * ct->cam.neg_posi.x;
			ret.y = ret.y + d.y * ct->cam.neg_posi.y;
			count++;
		}
		else
		{
			printf("neg_posi(%d %d)\n", ct->cam.neg_posi.x, ct->cam.neg_posi.y );
			printf("angle:%f\n", ct->cam.angle );
			ret.x = ret.x +  ct->cam.neg_posi.x * CUBESIZE;
			ret.y = ret.y +  ct->cam.neg_posi.y * CUBESIZE * ft_float_abs(tan(convert_degree_to_radian(ct->cam.angle)));
		}
		int_x = (int)ret.x;
		int_y = (int)ret.y;
		if (ret.x > (ct->mpp.x) || ret.x < 0 || ret.y < 0 || ret.y > ct->mpp.y)
		{
			ret.x = NO_WALL;
			ret.y = NO_WALL;
			printf("verrr There is no wall in this direction\n");
			return (ret);
		}
	}
	printf("verrrr wall found, wall position is (%f, %f)\n", ret.x, ret.y);
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

	while (ct->mpp.map[int_y - 1][int_x] == 0)  //attention for -1 here
	{
		if (count == 0)
		{
			ret.x = ret.x + d.x;
			ret.y = ret.y - d.y;
		//	printf("horizontal first round ret.x ret.y(%f, %f)\n", ret.x, ret.y);
			count++;
		}
		else
		{
			ret.y = ret.y - CUBESIZE;
			ret.x = ret.x + CUBESIZE / tan(convert_degree_to_radian(ct->cam.angle));
		//	printf("horizontal second and later round ret.x ret.y(%f, %f)\n", ret.x, ret.y);
		}
		int_x = (int)ret.x;
		int_y = (int)ret.y;
		//printf("wall valeur:%d\n", ct->mpp.map[int_y][int_ret.x]);
		if (ret.x > ct->mpp.x || ret.x < 0 || ret.y < 1 || ret.y > ct->mpp.y)
		{
			ret.x = NO_WALL;
			ret.y = NO_WALL;
			printf("horizontal There is no wall in this direction\n");
			return(ret) ;
		}
	}
	return (ret);
	printf("horizontal wall found, wall position is (%f, %f)\n", ret.x, ret.y);
}
