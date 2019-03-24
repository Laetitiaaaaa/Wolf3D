
#include "wolf3d.h"

void	draw_wall(t_context *ct)
{
	float	angle;
	int		x_pixel;

	angle = ct->cam.angle;
	x_pixel = XWIN / 2;
	draw_line_wall(ct, angle, x_pixel);
	while (x_pixel >= 0)
	{
		x_pixel--;
		angle += 30.0 / (float)(XWIN / 2);
		draw_line_wall(ct, angle, x_pixel);

	}
	angle = ct->cam.angle;
	x_pixel = XWIN / 2;
	while (x_pixel <= 499)
	{
		x_pixel++;
		angle -= 30.0 / (float)(XWIN / 2);
		draw_line_wall(ct, angle, x_pixel);
	}
}

void	draw_line_wall(t_context *ct, float angle, int	x_pixel)
{
	float		distance;
	int			wall_height;
	SDL_Point 	top;
	SDL_Point 	down;


	distance = dda_return_distance(ct, angle);
	if (distance < 0) // distance will be negative if no wall
		return ;
	wall_height = convert_mapdis_to_screendis(distance, ct);
	top.x = x_pixel;
	top.y = (YWIN - wall_height) / 2;
	down.x = x_pixel;
	down.y = (YWIN + wall_height) / 2;
	SDL_SetRenderDrawColor(ct->rend, 0, 51 , 102, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ct->rend, top.x, top.y, down.x, down.y);
}

int		convert_mapdis_to_screendis(float distance, t_context *ct)
{
	float	dis_max;
	int		wall_height;

	dis_max = sqrt(pow(ct->mpp.x, 2) + pow(ct->mpp.y, 2));

	//wall takes full screen when distance is 0    50% of screen when distance is 1
	if ((distance <= 1) && (distance >= 0))
	{
		wall_height = YWIN - (int)(distance * (float)YWIN / 2);
	}
	// wall take 5% of screen when distance is max
	if ((distance > 1) && (distance <= dis_max))
	{
		wall_height = (int)(250 - (0.45 * (float)YWIN / (dis_max - 1.0)) * (distance - 1.0));
	}
	return (wall_height);
}