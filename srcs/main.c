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

void	limit_menu(t_context *ct)
{
	while (ct->menu.in > 2)
		ct->menu.in -= 2;
	while (ct->menu.in < 0)
		ct->menu.in += 3;
}

void	loop_menu(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE)
	{
		while (SDL_PollEvent(&event))
		{
			limit_menu(ct);
			((state[SDL_SCANCODE_DOWN]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in + 1) % OUT : 0;
			((state[SDL_SCANCODE_UP]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = (ct->menu.in - 1) % OUT : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == PLAY)) ? loop(ct) : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == GUIDE)) ? loop_guide(ct) : 0;
			((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN) && (ct->menu.in == QUIT)) ? quit("Thank you for playing", ct) : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		print_menu(ct);
		SDL_RenderPresent(ct->rend);
	}
}

void	loop_guide(t_context *ct)
{
	Uint8			*state;
	SDL_Event		event;

	state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (TRUE && ct->menu.in != OUT)
	{
		while (SDL_PollEvent(&event))
		{
			((state[SDL_SCANCODE_SPACE]) && (event.type == SDL_KEYDOWN)) ? ct->menu.in = OUT : 0;
			common_actions(ct, state, event);
		}
		update_settings(ct);
		copy_texture_menu(ct, "./images/guides.bmp");		
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
