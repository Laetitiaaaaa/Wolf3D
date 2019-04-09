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
	SDL_Texture		*tmp;

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

void	limit_menu(t_context *ct)
{
	while (ct->menu.in > 2)
		ct->menu.in -= 2;
	while (ct->menu.in < 0)
		ct->menu.in += 3;
}

void	action_loop_menu(Uint8 *state, SDL_Event event, t_context *ct)
{
	((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN)
		&& (ct->menu.in == PLAY)) ? loop(ct) : 0;
	((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_UP]) && event.type
		== SDL_KEYDOWN) ? Mix_PlayChannel(MIX_DEFAULT_CHANNELS,
		ct->chunk_menu, 0) : 0;
	((state[SDL_SCANCODE_DOWN]) && (event.type == SDL_KEYDOWN)) ?
		ct->menu.in = (ct->menu.in + 1) % OUT : 0;
	((state[SDL_SCANCODE_UP]) && (event.type == SDL_KEYDOWN)) ?
		ct->menu.in = (ct->menu.in - 1) % OUT : 0;
	((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN)
		&& (ct->menu.in == GUIDE)) ? loop_guide(ct) : 0;
	((state[SDL_SCANCODE_RETURN]) && (event.type == SDL_KEYDOWN)
		&& (ct->menu.in == QUIT)) ?
		quit("Thank you for playing", ct) : 0;
	(event.type == SDL_QUIT) ? quit("Thank you for playing", ct) : 0;
}
