/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:53 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/15 14:27:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		loop(t_context *ct)
{
	while (TRUE)
	{
		SDL_SetRenderDrawColor(ct->rend, 124, 130, 140, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(ct->rend, 100, 100, 500, 100);
		SDL_RenderPresent(ct->rend);
	}
}