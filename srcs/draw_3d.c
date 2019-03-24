
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
	// int		D;
	// int		h;
	// int		H;
	// int		i;
	float		distance;
	int			wall_height;
	SDL_Point 	top;
	SDL_Point 	down;


	// i = 0;
	// D = 100;
	// h = 2;
	distance = dda_return_distance(ct, angle);
	if (distance < 0)
		return ;
	wall_height = convert_mapdis_to_screendis(distance, ct);
	top.x = x_pixel;
	top.y = (YWIN - wall_height) / 2;
	down.x = x_pixel;
	down.y = (YWIN + wall_height) / 2;
	SDL_SetRenderDrawColor(ct->rend, 0, 51 , 102, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(ct->rend, top.x, top.y, down.x, down.y);
}
// 	ct->pixel.y = YWIN / 2;
	// SDL_SetRenderDrawColor(ct->rend, 0, 51 , 102, SDL_ALPHA_OPAQUE);
// 	while (i < (H / 2))
// 	{
// 		SDL_RenderDrawPoint(ct->rend, ct->pixel.x, ct->pixel.y);
// 		ct->pixel.y++;
// 		i++;
// 	}
// 	i = 0;
// 	ct->pixel.y = YWIN / 2;
// 	while (i < (H / 2))
// 	{
// 		SDL_RenderDrawPoint(ct->rend, ct->pixel.x, ct->pixel.y);
// 		ct->pixel.y--;
// 		i++;
// 	}
// }

int		convert_mapdis_to_screendis(float distance, t_context *ct)
{
	float	dis_max;
	int		wall_height;

	if (ct->mpp.x > ct->mpp.y )
		dis_max = (float)(ct->mpp.x);
	else
		dis_max = (float)(ct->mpp.y);

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