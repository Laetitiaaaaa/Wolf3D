/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:58:28 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/14 14:58:30 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	error_info(int x)
{
	if (x == -2)
		ft_putendl("map file should not be empty");
	if (x == -3)
		ft_putendl("content of map file is not right");
	if (x == -1)
		ft_putendl("error");
	if (x == -4)
		ft_putendl("error:the length of each line should be the same");
}


int		init(t_context *ct, const char *argv)
{
	int		ret;

	ret = load_map(ct, argv);
	if (ret == -1 || ret == -2 || ret == -3 || ret == -4)
	{
		error_info(ret);
		return (0);
	}
	return (0);
}
