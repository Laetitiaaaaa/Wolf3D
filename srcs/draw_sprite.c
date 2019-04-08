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

static void		print_sprite_3d(t_context *ct, float distance, float sp_position_angle, int id)
{
	SDL_Rect	dst;
	int			sp_height;
	float		delta_angle;

	sp_height = convert_mapdis_to_screendis(distance, ct);
	delta_angle = sp_position_angle - ct->cam.angle;
	if (ft_float_abs(delta_angle) > 150 && sp_position_angle < ct->cam.angle )
		delta_angle = sp_position_angle + 360 - ct->cam.angle;
	else if (ft_float_abs(delta_angle) > 150)
		delta_angle = sp_position_angle - 360 - ct->cam.angle;
	// printf("delta_angle position camangle(%f, %f, %f)\n", delta_angle, sp_position_angle, ct->cam.angle );
	// printf("xpixel:%d\n",(int)(ct->xwin / 2 - ct->xwin * delta_angle / ANGLE));
	dst = define_rect((int)(ct->xwin / 2 - ct->xwin * delta_angle / ANGLE - sp_height / 2),(int)(ct->ywin / 2), sp_height, sp_height);
	if (id % 10 == KEY_CUBE)
		SDL_RenderCopy(ct->rend, ct->tex.key, NULL, &dst);
	if (id % 10 == MUSHROOM_CUBE)
		SDL_RenderCopy(ct->rend, ct->tex.mushroom, NULL, &dst);
	if (id % 10 == TUYAU_CUBE)
		SDL_RenderCopy(ct->rend, ct->tex.tuyau, NULL, &dst);
}

static void	draw_one_sprite_in_3d(t_context *ct, t_sp_lst *lst)
{
	float		sp_position_angle;
	float 		wall_dis;
	// float		delta_wall_angle;
	float		near_wall_dis_up;
	float		near_wall_dis_down;

	sp_position_angle = convert_rad_to_deg(atan2((lst->posi.y - ct->cam.posi.y) * (-1) , (lst->posi.x - ct->cam.posi.x)));
	sp_position_angle = angle_limit(sp_position_angle);
	wall_dis = dda_return_distance(ct, sp_position_angle);
	// delta_wall_angle = convert_rad_to_deg(atan(sqrt(2.0) / 2 / lst->distance));
	near_wall_dis_down = dda_return_distance(ct, angle_limit(sp_position_angle + 3.0));
	near_wall_dis_up = dda_return_distance(ct, angle_limit(sp_position_angle - 3.0));
	// if (wall_dis < 0 || wall_dis > lst->distance )
	if (wall_dis < 0 || (wall_dis > lst->distance && near_wall_dis_up > lst->distance && near_wall_dis_down > lst->distance))
	// if (wall_dis < 0 || wall_dis > lst->distance)
		print_sprite_3d(ct, lst->distance, sp_position_angle, lst->id);


}

int		walk_on_sprite(t_context *ct, t_floatpoint posi_sp)
{
	return ((((int)posi_sp.x) == ((int)ct->cam.posi.x) && ((int)posi_sp.y) == (int)ct->cam.posi.y));
}

void	pickup_sprite(t_context *ct, t_sp_lst *lst)
{
	t_point to_int;

	if ((lst->id)% 10 == KEY_CUBE)
		ct->sp.key_nb++;
	if ((lst->id)% 10 == MUSHROOM_CUBE)
		ct->sp.mushroom_nb++;
	Mix_PlayChannel(MIX_DEFAULT_CHANNELS, ct->chunk, 0);
	to_int.x = lst->posi.x;
	to_int.y = lst->posi.y;
	ct->mpp.map[to_int.y][to_int.x] = EMPTY;
}

void	draw_sprite_in_3d(t_context *ct)
{
	t_sp_lst *lst;

	ct->lst = sort_list(ct->lst);
	lst = ct->lst;
	while (lst != NULL)
	{
		if ((walk_on_sprite(ct, lst->posi) == TRUE) && (lst->id % 10 != TUYAU_CUBE))
			pickup_sprite(ct, lst);
		else
			draw_one_sprite_in_3d(ct, lst);
		lst = lst->next;

	}
	free_lst_sp(ct->lst);
	ct->lst = NULL;
	ct->at_least_one_sprite = FALSE;
}
