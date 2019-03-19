/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set_initial_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:17:16 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/19 15:17:17 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_set_initial_params(t_context *ct)
{
	ct->cam.cam_position.x = 2.2;
	ct->cam.cam_position.y = 2.2;
	ct->cam.angle = 10;
}