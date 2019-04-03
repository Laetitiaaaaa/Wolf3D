/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:29:52 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/31 16:29:54 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"



void	draw_one_sprite_in_2d(t_context *ct, t_floatpoint posi)
{
	SDL_Point		pixel;

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
	while (lst!= NULL)
	{
		draw_one_sprite_in_2d(ct, lst->posi);
		lst = lst->next;
	}
	free_lst_sp(ct->lst);
	ct->lst = NULL;
	ct->at_least_one_sprite = FALSE;
}

void		print_sprite_3d(t_context *ct, float distance, float sp_position_angle)
{
	SDL_Rect	dst;
	int			sp_height;
	float		delta_angle;

	sp_height = convert_mapdis_to_screendis(distance, ct);
	delta_angle = sp_position_angle - ct->cam.angle;
	dst.x = XWIN / 2 - XWIN / 60 * delta_angle;
	dst.y = YWIN / 2 ;
	dst.w = sp_height / 2;
	dst.h = sp_height / 2;
	SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst);

}
static void	draw_one_sprite_in_3d(t_context *ct, t_floatpoint posi)
{
	float		distance;
	float		sp_position_angle;
	float 		wall_dis;

	distance = sqrt(pow(posi.x - ct->cam.posi.x, 2) + pow(posi.y - ct->cam.posi.y, 2));
	sp_position_angle = convert_rad_to_deg(atan2((posi.y - ct->cam.posi.y) * (-1) , (posi.x - ct->cam.posi.x)));
	sp_position_angle = angle_limit(sp_position_angle);
	wall_dis = dda_return_distance(ct, sp_position_angle);
	if (wall_dis < 0 || wall_dis > distance )
		print_sprite_3d(ct, distance, sp_position_angle);
}

int		walk_on_sprite(t_context *ct, t_floatpoint posi_sp)
{
	if (((int)posi_sp.x == (int)ct->cam.posi.x) && ((int)posi_sp.x == (int)ct->cam.posi.x))
	{
		return (TRUE);
	}
	else
		return (FALSE);
}

// void	stock_sprite(t_context *ct)
// {
// 	{
// 		/* code */
// 	}
// }

void	draw_sprite_in_3d(t_context *ct)
{
	t_sp_lst *lst;

	lst = ct->lst;
	while (lst != NULL)
	{
		if (walk_on_sprite(ct, lst->posi) == TRUE)
		{
			// stock_sprite(ct);
			// printf("walk on sprite\n");
			lst = lst->next;

		}
		else
		{
			printf("camera posi(%f, %f) sprite posi(%f, %f)\n", ct->cam.posi.x, ct->cam.posi.y, lst->posi.x, lst->posi.y);
			draw_one_sprite_in_3d(ct, lst->posi);
			lst = lst->next;
		}

	}
	free_lst_sp(ct->lst);
	ct->lst = NULL;
	ct->at_least_one_sprite = FALSE;
}
















