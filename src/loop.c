/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 18:48:37 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_print_menu(t_context *ct)
{
	ct->surface = SDL_LoadBMP("../H_BJPIC.bmp");
	ct->surface == NULL ? exit(0) : 0;
	ct->tmp = SDL_CreateTextureFromSurface(ct->rend, ct->surface);
	SDL_FreeSurface(ct->surface);
	SDL_SetRenderTarget(ct->rend, ct->texture);
	SDL_RenderCopy(ct->rend, ct->tmp, NULL, NULL);
	SDL_DestroyTexture(ct->tmp);
	SDL_SetRenderTarget(ct->rend, NULL);
}

void		loop(t_context *ct)
{
	Uint8		*state;

	ft_print_menu(ct);
	while (TRUE)
	{
		SDL_PollEvent(ct->ev);
		state = (Uint8*)SDL_GetKeyboardState(NULL);
		state[SDL_SCANCODE_ESCAPE] ? exit(0) : 0;

		//----------------laeti
		SDL_RenderCopy(ct->rend, ct->texture, NULL, NULL);
		//----------------laeti-------
		SDL_RenderPresent(ct->rend);


	}
}
