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

void	quit(char *msg, t_context *ct)
{
	ft_putendl(msg);
	(void)ct;
	//codes to add :free the structure and all its contents here
	exit(0);
}

int main(int argc, char const **argv)
{
	t_context	ct;

	if (argc != 2)
	{
		ft_putendl("Usage : ./wolf3d <map file name>");
		return (0);
	}
	init(&ct, argv[1]);
	SDL_DestroyRenderer(ct.rend);
	SDL_DestroyWindow(ct.window);
	SDL_Quit();
	return 0;
}