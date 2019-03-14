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

int main(int argc, char const **argv)
{
	t_context	ct;

	if (argc != 2)
	{
		ft_putendl("Usage : ./wolf3d <map file name>");
		return (0);
	}
	if (init(&ct, argv[1]) != 0)
	{
		//a function to quit and print error info
		return (0);
	};
	return 0;
}