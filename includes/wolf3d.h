/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:06:38 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/21 19:28:08 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"
# include <stdio.h>

# define XWIN 1000.0
# define YWIN 800.0
# define X_SKY 2000
# define Y_SKY 400
# define X_CUT_SKY 600

# define CUBESIZE 1.0 // cubesize must be 1, otherwise plan2d calcu will not work
# define NO_WALL -1.0
# define WALL_CUBE 1
# define SPRITE_CUBE 2
# define INITIAL 0

typedef enum 		e_interface
{
	MAP = 0,
	GAME,
	INTERFACE_NB, // always leave it in the end
}					t_interface;

typedef enum 		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef enum 		e_neg_or_posi
{
	NEGATIVE = -1,
	POSITIVE = 1,
	ZERO = 0,
}					t_neg_or_posi;

typedef struct		s_map_params
{
	int				x;  // x and y are the number of points  Ex : for map 42, x = 10 y = 11
	int				y;
	int				**map;
}					t_map_params;

typedef struct 		s_floatpoint
{
	float			x;
	float			y;
}					t_floatpoint;

typedef struct  	s_camera
{
	t_floatpoint	posi;
	float			angle; // angle is between 0 and 360
	SDL_Point		neg_posi;
}					t_camera;

typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	t_camera		cam;
	SDL_Texture		*tex_ground;
	SDL_Texture		*tex_sky;
	int				sp_visible;
	t_floatpoint	sp_posi;

	SDL_Surface		*surface;
	SDL_Texture		*tmp;
	SDL_Texture		*texture;
	int				choose_inter;
}					t_context;

void				load_map(t_context *ct, const char *argv);
void				quit(char *msg, t_context *ct);
void				quit_nothing_to_free(char *msg);
void				free_map(t_context *ct);
int					init(t_context *ct, const char *argv);
void				loop(t_context *ct);
void				draw_background(t_context *ct);
double				convert_degree_to_radian(double angle);
SDL_Point			convert_plan_to_pixel(float x, float y, t_context *ct);
t_floatpoint		horizontal_first_delta_calcu(t_context *ct, float angle);
t_floatpoint		vertical_first_delta_calcu(t_context *ct, float angle);
t_floatpoint		vertical_wall_position_calcu(t_context *ct, float angle);
t_floatpoint		horizontal_wall_position_calcu(t_context *ct, float angle);
void				draw_2d(t_context *ct);
void				draw_cubes(t_context *ct);

void				key_events(t_context *ct, Uint8 *state);
void				draw_camera(t_context *ct);
void				draw_ray(t_context *ct, float angle);
float 				set_neg_posi(t_context *ct, float angle);
void				init_event(t_context *ct);
void				draw_wall(t_context *ct);
void				choose_interface(t_context *ct);
void				draw_wall(t_context *ct);
void				print_menu(t_context *ct);
void				draw_line_wall(t_context *ct, float angle, int	x_pixel);
int					convert_mapdis_to_screendis(float distance, t_context *ct);
t_floatpoint		dda_return_posi(t_context *ct, float angle);
float				dda_return_distance(t_context *ct, float angle);
void				key_events_movein_2d(t_context *ct, Uint8 *state);
void				key_events_movein_3d(t_context *ct, Uint8 *state);

void		draw_ground(t_context *ct);
float	angle_limit(float angle);
void	draw_sprite_in_2d(t_context *ct);
void		sprite_visible(t_context *ct, SDL_Point to_int);







#endif
