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

	if (lst == NULL)
	{
		lst = (t_sp_lst*)malloc(sizeof(t_sp_lst));
		current = lst;
	}
	else
	{
		while(lst != NULL)
			current = lst->next;
		current = (t_sp_lst*)malloc(sizeof(t_sp_lst));
	}
	current->posi = posi;
	current->visible = visible;
	current->id = id;
	current->next = NULL;
	return (lst);
}

// void		*lst_iter_id(t_sp_lst *lst, int id)
// {
// 	t_sp_lst	*current;

// 	current = lst;
// }

void		hit_sprite(t_context *ct, SDL_Point to_int)
{

	int				id;
	t_floatpoint	posi;
	int 			visible;

	visible = TRUE;
	posi.x = (float)to_int.x + (CUBESIZE / 2.0);
	posi.y = (float)to_int.y + (CUBESIZE / 2.0);
	id = ct->mpp.map[to_int.y][to_int.x];

	if (ct->lst == NULL)
	{
		ct->lst = lst_fill(ct->lst, id, posi, visible);
		printf("test%d\n", ct->lst->id);
	}


	ct->sp_visible = TRUE;
	ct->sp_posi.x = (float)to_int.x + (CUBESIZE / 2.0);
	ct->sp_posi.y = (float)to_int.y + (CUBESIZE / 2.0);
}

void	draw_sprite_in_2d(t_context *ct)
{
	SDL_Point		pixel;

	pixel = convert_plan_to_pixel(ct->sp_posi.x, ct->sp_posi.y, ct);
	// pixel = convert_plan_to_pixel((ct->spl->->posi.x, ((t_sprite*)(ct->sp_lst->content))->posi.y, ct);
	SDL_SetRenderDrawColor(ct->rend, 134, 244, 66, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x - 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x + 1, pixel.y);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y - 1);
	SDL_RenderDrawPoint(ct->rend, pixel.x, pixel.y + 1);
	ct->sp_visible = FALSE;
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

	distance = sqrt(pow(ct->sp_posi.x - ct->cam.posi.x, 2) + pow(ct->sp_posi.y - ct->cam.posi.y, 2));
	// distance = sqrt(pow(((t_sprite*)(ct->sp_lst->content))->posi.x - ct->cam.posi.x, 2)
		// + pow(((t_sprite*)(ct->sp_lst->content))->posi.y - ct->cam.posi.y, 2));
	sp_position_angle = convert_rad_to_deg(atan2((ct->sp_posi.y - ct->cam.posi.y) * (-1) , (ct->sp_posi.x - ct->cam.posi.x)));
	// sp_position_angle = convert_rad_to_deg(atan2(
		// (((t_sprite*)(ct->sp_lst->content))->posi.y - ct->cam.posi.y) * (-1),
		 // ((t_sprite*)(ct->sp_lst->content))->posi.x - ct->cam.posi.x));
	sp_position_angle = angle_limit(sp_position_angle);
	wall_dis = dda_return_distance(ct, sp_position_angle);
	if (wall_dis < 0 || wall_dis > distance )
		print_sprite(ct, distance, sp_position_angle);
	ct->sp_visible = FALSE;
}
