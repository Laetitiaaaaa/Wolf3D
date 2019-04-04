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
