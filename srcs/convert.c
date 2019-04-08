/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 10:41:09 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/16 10:41:11 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_point	convert_plan_to_pixel(float x, float y, t_context *ct)
{
	t_point	pixel;

	pixel.x = ct->xwin * x / ((ct->mpp.x) * CUBESIZE);
	pixel.y = ct->ywin * y / ((ct->mpp.y) * CUBESIZE);
	return (pixel);
}

double		convert_deg_to_rad(double angle)
{
	return (((double)angle) * M_PI / (double)180);
}

float		angle_limit(float angle)
{
	while (angle >= 360)
		angle = angle - 360;
	while (angle < 0)
		angle = angle + 360;
	return (angle);
}

double		convert_rad_to_deg(double radian)
{
	return (radian * ((double)180) / M_PI);
}
