/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_val_calculate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:42 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/04 12:59:44 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color				ft_color_val_calculate(int val_cl)
{
	t_color		cl;

	if (val_cl < 0)
		val_cl = -val_cl;
	while (val_cl > 360)
		val_cl = val_cl - 360;
	if (val_cl >= 0 && val_cl < 121)
	{
		cl.b = 0;
		cl.g = val_cl * (255 / 120);
		cl.r = 255 - cl.g;
	}
	else if (val_cl < 240)
	{
		cl.b = (val_cl - 120) * 255 / 120;
		cl.g = 255 - cl.b;
		cl.r = 0;
	}
	else
	{
		cl.r = (val_cl - 240) * 255 / 120;
		cl.g = 0;
		cl.b = 255 - cl.r;
	}
	return (cl);
}
