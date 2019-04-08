/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:51:58 by jleblond          #+#    #+#             */
/*   Updated: 2019/04/03 17:51:59 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_one_sprite_in_2d(t_context *ct, t_floatpoint posi)
{
	t_point		pixel;

	pixel = convert_plan_to_pixel(posi.x, posi.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 134, 244, 66, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x - 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x + 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y - 1);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y + 1);
}

void	draw_sprite_in_2d(t_context *ct)
{
	t_sp_lst *lst;

	lst = ct->lst;
	while (lst != NULL)
	{
		draw_one_sprite_in_2d(ct, lst->posi);
		lst = lst->next;
	}
	free_lst_sp(ct->lst);
	ct->lst = NULL;
	ct->at_least_one_sprite = FALSE;
}
