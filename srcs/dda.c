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

	if (ct->cam.angle > 90 && ct->cam.angle < 270)
	{
		d.x = ct->cam.cam_position.x - (float)(int)(ct->cam.cam_position.x);
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(ct->cam.angle)));
	}
	else
	{
		d.x = ((float)(int)(ct->cam.cam_position.x + 1)) - ct->cam.cam_position.x;
		d.y = ft_float_abs(d.x * tan(convert_degree_to_radian(ct->cam.angle)));
	}
	return (d);
}

void		set_neg_posi(t_context *ct)
{
	while (ct->cam.angle >= 360)
		ct->cam.angle = ct->cam.angle - 360;
	while (ct->cam.angle < 0)
		ct->cam.angle = ct->cam.angle + 360;
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
	t_floatpoint	detect;

	t_floatpoint	d = vertical_first_delta_calcu(ct);
	int				count = 0;
	SDL_Point		to_int;

	detect.x = ct->cam.cam_position.x;
	detect.y = ct->cam.cam_position.y;
	to_int.x = (int)detect.x;
	to_int.y = (int)detect.y;

	set_neg_posi(ct);
	if ((ct->cam.angle == 90) || (ct->cam.angle == 270))
	{
		detect.x = NO_WALL;
		detect.y = NO_WALL;
		return(detect);
	}
	while (ct->mpp.map[to_int.y][to_int.x] == 0)
	{
		if (count == 0)
		{
			detect.x = detect.x + d.x * ct->cam.neg_posi.x;
			detect.y = detect.y + d.y * ct->cam.neg_posi.y;
			count++;
		}
		else
		{
			detect.x = detect.x +  ct->cam.neg_posi.x * CUBESIZE;
			detect.y = detect.y +  ct->cam.neg_posi.y * CUBESIZE * ft_float_abs(tan(convert_degree_to_radian(ct->cam.angle)));

		}
		to_int.x = (int)detect.x;
		to_int.y = (int)detect.y;
		if (ct->cam.angle > 90 && ct->cam.angle < 270)
			to_int.x--;
		if (detect.x > ct->mpp.x - 1 || detect.x < 1 || detect.y < 0 || detect.y > ct->mpp.y)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
			return (detect);
		}
	}
	return(detect);
}

