/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 10:27:32 by llejeune          #+#    #+#             */
/*   Updated: 2019/03/18 14:54:01 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	copy_texture_menu(t_context *ct, char *path)
{
	SDL_Texture 	*tmp;

	tmp = init_texture(path, ct);
	SDL_SetRenderTarget(ct->rend, ct->menu.texture);
	SDL_RenderCopy(ct->rend, tmp, NULL, NULL);
	SDL_DestroyTexture(tmp);
	SDL_SetRenderTarget(ct->rend, NULL);
}

void	print_menu(t_context *ct)
{
	if (ct->menu.in == PLAY)
		copy_texture_menu(ct, "./images/play.bmp");
	if (ct->menu.in == GUIDE)
		copy_texture_menu(ct, "./images/menuguide.bmp");
	if (ct->menu.in == QUIT)
		copy_texture_menu(ct, "./images/quit.bmp");
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
