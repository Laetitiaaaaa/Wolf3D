/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 10:27:32 by llejeune          #+#    #+#             */
/*   Updated: 2019/03/16 10:28:02 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_print_menu(t_context *ct)
{
	ct->surface = SDL_LoadBMP("../wolf3d.bmp");
	ct->surface == NULL ? exit(0) : 0;
	ct->tmp = SDL_CreateTextureFromSurface(ct->rend, ct->surface);
	SDL_FreeSurface(ct->surface);
	SDL_SetRenderTarget(ct->rend, ct->texture);
	SDL_RenderCopy(ct->rend, ct->tmp, NULL, NULL);
	SDL_DestroyTexture(ct->tmp);
	SDL_SetRenderTarget(ct->rend, NULL);
}
