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

	if (ct->cam.angle > 0 && ct->cam.angle < 180)
	{
		d.y = ct->cam.cam_position.y -(float)(int)(ct->cam.cam_position.y);
		d.x = ft_float_abs(d.y / tan(convert_degree_to_radian(ct->cam.angle)));
	}
	else
	{
		d.y = (float)(int)(ct->cam.cam_position.y) + 1 - ct->cam.cam_position.y;
		d.x = ft_float_abs(d.y / tan(convert_degree_to_radian(ct->cam.angle)));
	}
	return (d);
}

t_floatpoint		horizontal_wall_position_calcu(t_context *ct)
{
	t_floatpoint	detect;
	t_floatpoint	d = horizontal_first_delta_calcu(ct);

	detect.x = ct->cam.cam_position.x;
	detect.y = ct->cam.cam_position.y;
	int				count = 0;
	SDL_Point		to_int;

	to_int.x = (int)detect.x;
	to_int.y = (int)detect.y;

	set_neg_posi(ct);
	if ((ct->cam.angle == 0) || (ct->cam.angle == 180))
	{
		detect.x = NO_WALL;
		detect.y = NO_WALL;
		return(detect);
	}
	while (ct->mpp.map[to_int.y][to_int.x] == 0)  //attention for -1 here
	{
		if (count == 0)
		{
			detect.x = detect.x + d.x * ct->cam.neg_posi.x;
			detect.y = detect.y + d.y * ct->cam.neg_posi.y;
	//		printf("horizontal first round detect.x detect.y(%f, %f)\n", detect.x, detect.y);
			count++;
		}
		else
		{
			detect.y = detect.y +  ct->cam.neg_posi.y * CUBESIZE;
			detect.x = detect.x +  ct->cam.neg_posi.x * CUBESIZE / ft_float_abs(tan(convert_degree_to_radian(ct->cam.angle)));
//			printf(" horizontal other round to_int x and y(%d, %d)   map[][] :%d\n", to_int.x, to_int.y, ct->mpp.map[to_int.y][to_int.x]);
		}
		to_int.x = (int)detect.x;
		to_int.y = (int)detect.y;
		if (ct->cam.angle > 0 && ct->cam.angle < 180)
		{
			to_int.y--;
		}
		if (detect.x > ct->mpp.x || detect.x < 0 || detect.y < 1 || detect.y > ct->mpp.y - 1)
		{
			detect.x = NO_WALL;
			detect.y = NO_WALL;
//			printf("horizontal There is no wall in this direction\n");
			return(detect) ;
		}
	}
	// printf("neg_posi(%d %d)\n", ct->cam.neg_posi.x, ct->cam.neg_posi.y );
	// printf("angle:%f\n", ct->cam.angle );
	// printf("horrrr wall found, wall position is (%f, %f)\n", detect.x, detect.y);
	// printf("to_int x and y(%d, %d)   map[][] :%d\n", to_int.x, to_int.y, ct->mpp.map[to_int.y][to_int.x]);
	return (detect);

}