
#include "wolf3d.h"

void	draw_wall(t_context *ct)
{
	float	angle;

	angle = ct->cam.angle;
	ct->pixel.x = XWIN / 2;
	draw_line_wall(ct, angle);
	while (angle <= (ct->cam.angle + 30))
	{
		ct->pixel.x++;
		angle += 30.0 / 500.0;
		draw_line_wall(ct, angle);

	}
	angle = ct->cam.angle;

	ct->pixel.x = XWIN / 2;
	while (angle2 >= (ct->cam.angle - 30))
	{
		ct->pixel.x--;
		angle2 -= 30.0 / 500.0;
		draw_line_wall(ct, angle2);
	}
}

void	draw_line_wall(t_context *ct, float angle)
{
	int		D;
	int		h;
	int		H;
	int		i;

	i = 0;
	D = 200;
	h = 4;
	dda(ct, angle);
	ct->distance_ver < ct->distance_hor ? (ct->distance = ct->distance_ver) : (ct->distance = ct->distance_hor);
	H = (D * h) / ct->distance;
	ct->pixel.y = YWIN / 2;
	SDL_SetRenderDrawColor(ct->rend, 86, 11 , 209, SDL_ALPHA_OPAQUE);
	while (i < (H / 2))
	{
		SDL_RenderDrawPoint(ct->rend, ct->pixel.x, ct->pixel.y);
		ct->pixel.y++;
		i++;
	}
	i = 0;
	ct->pixel.y = YWIN / 2;
	while (i < (H / 2))
	{
		SDL_RenderDrawPoint(ct->rend, ct->pixel.x, ct->pixel.y);
		ct->pixel.y--;
		i++;
	}
}