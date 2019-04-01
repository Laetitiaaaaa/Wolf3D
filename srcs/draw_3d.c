
#include "wolf3d.h"

void	draw_wall(t_context *ct)
{
	float	angle;
	int		x_pixel;

	SDL_QueryTexture(ct->wall.motif_red, NULL, NULL, &ct->wall.width, &ct->wall.height);
	angle = ct->cam.angle;
	x_pixel = XWIN / 2;
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

SDL_Rect	define_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;
	
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

void	draw_line_wall(t_context *ct, float angle, int	x_pixel)
{
	float		distance;
	int			wall_height;
	SDL_Point 	top;
	SDL_Point 	down;
	t_floatpoint wall;

	SDL_Rect 	src;
	SDL_Rect 	dst;
	float 		pos_text;

	pos_text = 0.0;
	wall = dda_return_posi(ct, angle);
	distance = dda_return_distance(ct, angle);
	if (distance < 0) // distance will be negative if no wall
		return ;
	wall_height = convert_mapdis_to_screendis(distance, ct);
	top.x = x_pixel;
	top.y = (YWIN - wall_height) / 2;
	down.x = x_pixel;
	down.y = (YWIN + wall_height) / 2;

	dst = define_rect(x_pixel, top.y, 1, wall_height);	

	while (angle >= 360)
		angle = angle - 360;
	while (angle < 0)
		angle = angle + 360;
	
	if (((int)(wall.x * 10000.0) % 10000) == 0 && (angle >= 90 && angle <= 270))
	{
		pos_text = wall.y * ct->wall.width / (int)(wall.y + 1);
		src = define_rect((int)pos_text, 0, 1, ct->wall.height);
		if (SDL_RenderCopy(ct->rend, ct->wall.motif_red, &src, &dst) < 0)
			quit("SDL_SetRenderCopy RED failed\n", ct);
	}
	else if (((int)(wall.y * 10000.0) % 10000) == 0 && (angle >= 0 && angle <= 180))
	{
		pos_text = wall.x * ct->wall.width / (int)(wall.x + 1);
		src = define_rect((int)pos_text, 0, 1, ct->wall.height);
		if (SDL_RenderCopy(ct->rend, ct->wall.motif_yellow, &src, &dst) < 0)
			quit("SDL_SetRenderCopy YELLOW failed\n", ct);
	}
	else if (((int)(wall.y * 10000.0) % 10000) == 0 && (angle >= 180 && angle < 360))
	{
		pos_text = wall.x * ct->wall.width / (int)(wall.x + 1);
		src = define_rect((int)pos_text, 0, 1, ct->wall.height);
		if (SDL_RenderCopy(ct->rend, ct->wall.motif_green, &src, &dst) < 0)
			quit("SDL_SetRenderCopy GREEN failed\n", ct);
	}
	else if (((int)(wall.x * 10000.0) % 10000) == 0 && ((angle >= 270 && angle < 360) || (angle >= 0 && angle <= 90)))
	{
		pos_text = wall.y * ct->wall.width / (int)(wall.y + 1);
		src = define_rect((int)pos_text, 0, 1, ct->wall.height);
		if (SDL_RenderCopy(ct->rend, ct->wall.motif_blue, &src, &dst) < 0)
			quit("SDL_SetRenderCopy BLUE failed\n", ct);
	}
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


	wall_height = (int)((dis_max - distance) * 50.0 / distance) + 5;
	if (wall_height > YWIN)
		wall_height = YWIN;
	return (wall_height);
}













