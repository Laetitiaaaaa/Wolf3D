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

float		dda_return_distance(t_context *ct, float angle) // fisheye corrected in this dda fucntion
{
	t_floatpoint 	posi_ver;
	t_floatpoint 	posi_hor;
	float 			distance_ver;
	float 			distance_hor;


	posi_ver = vertical_wall_position_calcu(ct, angle);
	posi_hor = horizontal_wall_position_calcu(ct, angle);
	distance_ver = ft_float_abs((posi_ver.x - ct->cam.posi.x) * cos(convert_degree_to_radian(ct->cam.angle)))
	+ ft_float_abs((posi_ver.y - ct->cam.posi.y) * sin(convert_degree_to_radian(ct->cam.angle)));
	distance_hor = ft_float_abs((posi_hor.x - ct->cam.posi.x) * cos(convert_degree_to_radian(ct->cam.angle)))
	+ ft_float_abs((posi_hor.y - ct->cam.posi.y) * sin(convert_degree_to_radian( ct->cam.angle)));
	if (posi_ver.x == NO_WALL && posi_hor.x == NO_WALL)
		return (NO_WALL);
	else if (posi_ver.x == NO_WALL)
		return (distance_hor);
	else if (posi_hor.x == NO_WALL)
		return(distance_ver);
	else if (distance_ver < distance_hor)
		return (distance_ver);
	else
		return(distance_hor);
}

t_floatpoint		dda_return_posi(t_context *ct, float angle)
{
	t_floatpoint 	posi_ver;
	t_floatpoint 	posi_hor;
	float 			distance_ver;
	float 			distance_hor;

	distance_hor = INITIAL;
	distance_ver = INITIAL;
	posi_ver = vertical_wall_position_calcu(ct, angle);
	posi_hor = horizontal_wall_position_calcu(ct, angle);


	if (posi_ver.x == NO_WALL && posi_hor.x == NO_WALL)
		return (posi_ver);
	else if (posi_ver.x == NO_WALL)
		return (posi_hor);
	else if (posi_hor.x == NO_WALL)
		return (posi_ver);
	else
	{
		distance_ver = sqrt(pow(posi_ver.x - ct->cam.posi.x, 2) + pow(posi_ver.y - ct->cam.posi.y, 2));
		distance_hor = sqrt(pow(posi_hor.x - ct->cam.posi.x, 2) + pow(posi_hor.y - ct->cam.posi.y, 2));
		return (distance_ver < distance_hor ? posi_ver : posi_hor);
	}
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

