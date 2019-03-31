
#include "wolf3d.h"

void	draw_wall(t_context *ct)
{
	float	angle;
	int		x_pixel;
	int		count;

	count = 0;
	angle = ct->cam.angle + 30;
	x_pixel = 0;
	while (x_pixel < XWIN)
	{
		angle -= 60.0 / ((float)XWIN);
		x_pixel++;
		draw_line_wall(ct, angle, x_pixel);
		if ((ct->sp_visible == TRUE) && (count == 0))
		{
			count++;
			draw_sprite_in_3d(ct, angle);
		}
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
	wall_height = (int)((dis_max - distance) * 20.0 / distance) + 5;
	if (wall_height > YWIN)
		wall_height = YWIN;
	return (wall_height);
}