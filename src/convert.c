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


//je vais normaliser les points sur plan entre 0 et 1
SDL_Point	convert_plan_to_pixel(t_floatpoint n, t_context *ct)
{
	SDL_Point	pixel;

	pixel.x = XWIN * n.x / ((ct->mpp.x - 1) * CUBESIZE);
	pixel.y = YWIN * n.y / ((ct->mpp.y - 1) * CUBESIZE);
	return (pixel);
}

double		convert_degree_to_radian(double angle)
{
	return(((double)angle) * M_PI / (double)180);
}