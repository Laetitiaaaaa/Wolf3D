/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:22:27 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/14 09:22:29 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quit(char *info, t_context *ct)
{
	ft_putendl(info);
	(void)ct;
	// do free here
	exit(0);
}

int 	main(int argc, char const **argv)
{
	t_context	ct;

	if (argc != 2)
		quit("Usage : ./wolf3d <map file name>", &ct);
	if (init(&ct, argv[1]) != 0)
		quit("initialtion failed", &ct);
	return (0);
}


