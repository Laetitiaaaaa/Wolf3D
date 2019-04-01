/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:58:49 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/19 15:58:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_event(t_context *ct)
{
	ct->menu.in = 1;
	ct->cam.posi.x = 2.2;
	ct->cam.posi.y = 2.2;
	ct->cam.angle = 5.0;
	ct->choose_inter = MENU;
}
