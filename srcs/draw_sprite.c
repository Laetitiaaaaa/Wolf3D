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


t_sp_lst	*lst_fill(t_sp_lst *lst, int id, t_floatpoint posi, int visible)
{
	t_sp_lst	*current;

	current = lst;
	if (current == NULL)
	{
		lst = (t_sp_lst*)malloc(sizeof(t_sp_lst));
		current = lst;
	}
	else
	{
		while(current->next != NULL)
			current = current->next;
		current->next = (t_sp_lst*)malloc(sizeof(t_sp_lst)); // malloc not freeed
		current = current->next;
	}
	current->posi = posi;
	current->visible = visible;
	current->id = id;
	current->next = NULL;
	return (lst);
}

int		lst_new_sprite_check(t_sp_lst *lst, int id)
{
	int			new_sprite;

	if (lst == NULL)
		return (new_sprite = TRUE);
	while (lst != NULL)
	{
		if (lst->id == id)
			return(new_sprite = FALSE);
		lst = lst->next;
	}
	return (new_sprite = TRUE);
}

void		hit_sprite(t_context *ct, SDL_Point to_int)
{

	int				id;
	t_floatpoint	posi;
	int 			visible;

	ct->at_least_one_sprite = TRUE;

	visible = TRUE;
	posi.x = (float)to_int.x + (CUBESIZE / 2.0);
	posi.y = (float)to_int.y + (CUBESIZE / 2.0);
	id = ct->mpp.map[to_int.y][to_int.x];

	if (lst_new_sprite_check(ct->lst, id) == TRUE)
	{
		ct->lst = lst_fill(ct->lst, id, posi, visible);
	}
}


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

	draw_one_sprite_in_2d(ct, ct->lst->posi);
	ct->at_least_one_sprite = FALSE;
}



void		print_sprite(t_context *ct, float distance, float sp_position_angle)
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
void	draw_sprite_in_3d(t_context *ct)
{
	float		distance;
	float		sp_position_angle;
	float 		wall_dis;

	distance = sqrt(pow(ct->lst->posi.x - ct->cam.posi.x, 2) + pow(ct->lst->posi.y - ct->cam.posi.y, 2));
	sp_position_angle = convert_rad_to_deg(atan2((ct->lst->posi.y - ct->cam.posi.y) * (-1) , (ct->lst->posi.x - ct->cam.posi.x)));
	sp_position_angle = angle_limit(sp_position_angle);
	wall_dis = dda_return_distance(ct, sp_position_angle);
	if (wall_dis < 0 || wall_dis > distance )
		print_sprite(ct, distance, sp_position_angle);
	ct->at_least_one_sprite = FALSE;
}
