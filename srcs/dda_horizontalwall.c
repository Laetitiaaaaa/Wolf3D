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

t_floatpoint		horizontal_first_delta_calcu(t_context *ct, float angle)
{
	t_floatpoint	delta;

	angle = set_neg_posi(ct, angle);
	if (angle > 0 && angle < 180)
	{
		delta.y = ct->cam.posi.y -(float)(int)(ct->cam.posi.y);
		delta.x = ft_float_abs(delta.y / tan(convert_degree_to_radian(angle)));
	}
	else
	{
		delta.y = (float)(int)(ct->cam.posi.y) + 1 - ct->cam.posi.y;
		delta.x = ft_float_abs(delta.y / tan(convert_degree_to_radian(angle)));
	}
	return (delta);
}

t_floatpoint		first_horizontal_step(t_context *ct, float angle, t_floatpoint detect)
{
	t_floatpoint	delta;

	delta = horizontal_first_delta_calcu(ct, angle);
	detect.x += delta.x * ct->cam.neg_posi.x;
	detect.y += delta.y * ct->cam.neg_posi.y;
	return (detect);
}

t_floatpoint		continue_horizontal_step(t_context *ct, float angle, t_floatpoint detect)
{
	detect.x += ct->cam.neg_posi.x * CUBESIZE
	/ ft_float_abs(tan(convert_degree_to_radian(angle)));
	detect.y += ct->cam.neg_posi.y * CUBESIZE;
	return (detect);
}

t_floatpoint 		sub_horizontal(t_context *ct, float angle, t_floatpoint detect, SDL_Point to_int)
{
	int				count;

	count = 0;
	while (ct->mpp.map[to_int.y][to_int.x] != WALL_CUBE)  //attention for -1 here
	{
		if (count == 0)
		{
			detect = first_horizontal_step(ct, angle, detect);
			count++;
		}
		else
			detect = continue_horizontal_step(ct, angle, detect);
		to_int.x = (int)detect.x;
		to_int.y = (int)detect.y;

		if (angle > 0 && angle < 180)
			to_int.y--;
		if (detect.x >= ct->mpp.x || detect.x <= 0 || detect.y < 1 || detect.y > ct->mpp.y - 1)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
			return(detect) ;
		}
		if (ct->mpp.map[to_int.y][to_int.x] == 2)
			sprite_visible(ct, detect, to_int, angle);
	}
	return (detect);
}


t_floatpoint		horizontal_wall_position_calcu(t_context *ct, float angle)
{
	t_floatpoint	detect;
	SDL_Point		to_int;

	detect.x = ct->cam.posi.x;
	detect.y = ct->cam.posi.y;
	to_int.x = (int)detect.x;
	to_int.y = (int)detect.y;
	angle = set_neg_posi(ct, angle);
	if ((angle == 0) || (angle == 180))
	{
		detect.x = NO_WALL;
		detect.y = NO_WALL;
		return(detect);
	}
	detect = sub_horizontal(ct, angle, detect, to_int);
	return (detect);
}
