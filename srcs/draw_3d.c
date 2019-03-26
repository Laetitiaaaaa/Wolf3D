
#include "wolf3d.h"

void	draw_wall(t_context *ct)
{
	float	angle;
	int		x_pixel;

	angle = ct->cam.angle;
	x_pixel = XWIN / 2;
//	draw_line_wall(ct, angle, x_pixel);
	while (x_pixel >= 0)
	{
		angle += 30.0 / (float)(XWIN / 2);
		draw_line_wall(ct, angle, x_pixel);
		x_pixel--;
	}
	angle = ct->cam.angle;
	x_pixel = XWIN / 2;
	while (x_pixel < XWIN)
	{
		angle -= 30.0 / (float)(XWIN / 2);
		draw_line_wall(ct, angle, x_pixel);
		x_pixel++;
	}
}

void	draw_line_wall(t_context *ct, float angle, int	x_pixel)
{
	float		distance;
	int			wall_height;
	SDL_Point 	top;
	SDL_Point 	down;
	t_floatpoint wall;

	// SDL_Rect 	src;
	// SDL_Rect 	dst;

	wall = dda_return_posi(ct, angle);
	distance = dda_return_distance(ct, angle);
	if (distance < 0) // distance will be negative if no wall
		return ;
	wall_height = convert_mapdis_to_screendis(distance, ct);
	top.x = x_pixel;
	top.y = (YWIN - wall_height) / 2;
	down.x = x_pixel;
	down.y = (YWIN + wall_height) / 2;

	// SDL_QueryTexture(ct->wall_texture, NULL, NULL, &src.x, &src.h);
	// src.x = src.x/ 2;
	// src.y = 0;
	// src.w = 1;
	while (angle >= 360)
		angle = angle - 360;
	while (angle < 0)
		angle = angle + 360;
	// dst.x = x_pixel;
	// dst.y = top.y;
	// dst.w = 1;
	// dst.h = wall_height + 1;

	if (((int)(wall.x * 10000.0) % 10000) == 0 && (angle >= 90 && angle <= 270))
		SDL_SetRenderDrawColor(ct->rend, 255, 150, 255, SDL_ALPHA_OPAQUE);
	else if (((int)(wall.y * 10000.0) % 10000) == 0 && (angle >= 0 && angle <= 180))
		SDL_SetRenderDrawColor(ct->rend, 255, 200, 0, SDL_ALPHA_OPAQUE);
	else if (((int)(wall.y * 10000.0) % 10000) == 0 && (angle >= 180 && angle < 360))
	 	SDL_SetRenderDrawColor(ct->rend, 255, 0, 100, SDL_ALPHA_OPAQUE);
	else if (((int)(wall.x * 10000.0) % 10000) == 0 && ((angle >= 270 && angle < 360) || (angle >= 0 && angle <= 90)))
		SDL_SetRenderDrawColor(ct->rend, 50, 225, 175, SDL_ALPHA_OPAQUE);
//		SDL_SetRenderDrawColor(ct->rend, (int)(angle * 255) >> 3, 0, (int)(angle * 255) >> 3, SDL_ALPHA_OPAQUE);
	
	// // SDL_SetRenderDrawColor(ct->rend, angle * 255 / 10, 0, angle * 255 / 10, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ct->rend, top.x, top.y, down.x, down.y);
	
	// if (SDL_RenderCopy(ct->rend, ct->wall_texture, &src, &dst) < 0)// NE PAS OUBLIER DE FREE LA TEXTURE A LA FIN
	// 	quit("SDL_SetRenderCopy failed\n", ct);
}

int		convert_mapdis_to_screendis(float distance, t_context *ct)
{
	float	dis_max;
	// float	dis_min;
	int		wall_height;

	dis_max = sqrt(pow(ct->mpp.x, 2) + pow(ct->mpp.y, 2));
	// dis_min = 0.1;
	// if (distance < dis_min)
	// 	distance = dis_min;

	// wall_height = YWIN - ((distance - dis_min) / (dis_max - dis_min) * YWIN) + 10;


	wall_height = (int)((dis_max - distance) * 20.0 / distance) + 5;
	if (wall_height > YWIN)
		wall_height = YWIN;
	return (wall_height);
}













