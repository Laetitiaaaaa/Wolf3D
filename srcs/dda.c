/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:11:24 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/21 19:27:18 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_floatpoint		dda(t_context *ct, float angle)
{
	t_floatpoint 	posi_ver;
	t_floatpoint 	posi_hor;

	posi_ver = vertial_wall_position_calcu(ct, angle);
	posi_hor = horizontal_wall_position_calcu(ct, angle);
	ct->distance_ver = ft_float_abs((((float)posi_ver.x) - ct->cam.cam_position.x) / cos(convert_degree_to_radian(angle)));
	ct->distance_hor = ft_float_abs((ct->cam.cam_position.y - (float)posi_hor.y) / sin(convert_degree_to_radian(angle)));
	if (posi_ver.x == NO_WALL && posi_hor.x == NO_WALL)
		return (posi_ver);
	else if (posi_ver.x == NO_WALL)
		return (posi_hor);
	else if (posi_hor.x == NO_WALL)
		return (posi_ver);
	else
		return(ct->distance_ver < ct->distance_hor ? posi_ver : posi_hor);
}


t_floatpoint		vertical_first_delta_calcu(t_context *ct, float angle)
{
	t_floatpoint	d;

	angle = set_neg_posi(ct, angle);
	if (angle > 90 && angle < 270)
	{
		d.x = ct->cam.cam_position.x - (float)(int)(ct->cam.cam_position.x);
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(angle)));
	}
	else
	{
		d.x = ((float)(int)(ct->cam.cam_position.x + 1)) - ct->cam.cam_position.x;
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(angle)));
	}
	return (d);
}

float 	set_neg_posi(t_context *ct, float angle)
{
	while (angle >= 360)
		angle = angle - 360;
	while (angle < 0)
		angle = angle + 360;
	if ((angle > 0) && (angle < 90))
	{
		ct->cam.neg_posi.x = POSITIVE;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if (angle == 90)
	{
		ct->cam.neg_posi.x = ZERO;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if ((angle > 90) && (angle <= 180))
	{
		ct->cam.neg_posi.x = NEGATIVE;
		ct->cam.neg_posi.y = NEGATIVE;
	}
	if ((angle > 180) && (angle < 270))
	{
		ct->cam.neg_posi.x = NEGATIVE;
		ct->cam.neg_posi.y = POSITIVE;
	}
	if (angle == 270)
	{
		ct->cam.neg_posi.x = ZERO;
		ct->cam.neg_posi.y = POSITIVE;
	}
	if ((angle > 270) && (angle < 360))
	{
		ct->cam.neg_posi.x = POSITIVE;
		ct->cam.neg_posi.y = POSITIVE;
	}
	return (angle);
}

t_floatpoint			vertial_wall_position_calcu(t_context *ct, float angle)
{
	t_floatpoint	detect;

	t_floatpoint	d = vertical_first_delta_calcu(ct, angle);
	int				count = 0;
	SDL_Point		to_int;

	detect.x = ct->cam.cam_position.x;
	detect.y = ct->cam.cam_position.y;
	to_int.x = (int)detect.x;
	to_int.y = (int)detect.y;

	angle = set_neg_posi(ct, angle);
	if ((angle == 90) || (angle == 270))
	{
		detect.x = NO_WALL;
		detect.y = NO_WALL;
		return(detect);
	}
	while (ct->mpp.map[to_int.y][to_int.x] == 0)
	{
		if (count == 0)
		{
			detect.x += d.x * ct->cam.neg_posi.x;
			detect.y += d.y * ct->cam.neg_posi.y;
			count++;

		}
		else
		{
			detect.x += ct->cam.neg_posi.x * CUBESIZE;
			detect.y += ct->cam.neg_posi.y * CUBESIZE * ft_float_abs(tan(convert_degree_to_radian(angle)));
		}
		to_int.x = (int)detect.x;
		to_int.y = (int)detect.y;
		if (angle > 90 && angle < 270)
			to_int.x--;
		if (detect.x > ct->mpp.x - 1 || detect.x < 1 || detect.y <= 0 || detect.y >= ct->mpp.y)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
			return (detect);
		}
	}
	return(detect);
}

