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
	distance_ver = sqrt(pow(posi_ver.x - ct->cam.posi.x, 2)
		+ pow(posi_ver.y - ct->cam.posi.y, 2))
	* ft_float_abs(cos(convert_deg_to_rad(angle - ct->cam.angle)));
	distance_hor = sqrt(pow(posi_hor.x - ct->cam.posi.x, 2)
		+ pow(posi_hor.y - ct->cam.posi.y, 2))
	* ft_float_abs(cos(convert_deg_to_rad(angle - ct->cam.angle)));
	if (posi_ver.x == NO_WALL && posi_hor.x == NO_WALL)
		return (NO_WALL);
	else if (posi_ver.x == NO_WALL)
		return (distance_hor);
	else if (posi_hor.x == NO_WALL)
		return(distance_ver);
	else if (distance_ver < distance_hor)
		return (distance_ver);
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
	distance_ver = sqrt(pow(posi_ver.x - ct->cam.posi.x, 2)
		+ pow(posi_ver.y - ct->cam.posi.y, 2));
	distance_hor = sqrt(pow(posi_hor.x - ct->cam.posi.x, 2)
		+ pow(posi_hor.y - ct->cam.posi.y, 2));
	return (distance_ver < distance_hor ? posi_ver : posi_hor);
}

void	val_cam_neg_posi(t_context *ct, int a, int b)
{
	ct->cam.neg_posi.x = a;
	ct->cam.neg_posi.y = b;
}

float 	set_neg_posi(t_context *ct, float angle)
{
	angle = angle_limit(angle);
	((angle > 0) && (angle < 90)) ? val_cam_neg_posi(ct, POSITIVE, NEGATIVE) : 0;
	(angle == 90) ? val_cam_neg_posi(ct, ZERO, NEGATIVE) : 0;
	((angle > 90) && (angle <= 180)) ? val_cam_neg_posi(ct, NEGATIVE, NEGATIVE) : 0;
	((angle > 180) && (angle < 270)) ? val_cam_neg_posi(ct, NEGATIVE, POSITIVE) : 0;
	(angle == 270) ? val_cam_neg_posi(ct, ZERO, POSITIVE) : 0;
	((angle > 270) && (angle < 360)) ? val_cam_neg_posi(ct, POSITIVE, POSITIVE) : 0;
	return (angle);
}

