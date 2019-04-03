/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:22:27 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 16:22:05 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	loop_menu(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		while (SDL_PollEvent(&event))
		{
			while (ct->menu.in > 2)
				ct->menu.in -= 2;
			while (ct->menu.in < 0)
				ct->menu.in += 3;
			((state[SDL_SCANCODE_DOWN]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in + 1) % OUT : 0;
			((state[SDL_SCANCODE_UP]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in - 1) % OUT : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == PLAY)) ? loop(ct) : 0;
		}
		key_events(ct, state);
		print_menu(ct);
		SDL_RenderPresent(ct->rend);
	}
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
	loop_menu(&ct);
	return (0);
}
