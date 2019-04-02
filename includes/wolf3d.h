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
# include "SDL_image.h"
# include <stdio.h>

# define XWIN 1000.0
# define YWIN 800.0
# define X_SKY 2000
# define Y_SKY 400
# define X_CUT_SKY 600

# define CUBESIZE 1.0 // cubesize must be 1, otherwise plan2d calcu will not work
# define NO_WALL -1.0
# define INITIAL 0

typedef enum  		e_map_content
{
	EMPTY = 0,
	WALL_CUBE,
	CAM_CUBE,
	SPRITE_CUBE,
}					t_map_content;

typedef enum 		e_interface
{
	// MENU = 0,
	GAME = 0,
	MAP,
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

typedef struct 		s_wall_texture
{
	SDL_Texture 	*motif_red;
	SDL_Texture		*motif_yellow;
	SDL_Texture		*motif_green;
	SDL_Texture		*motif_blue;
	int 			width;
	int 			height;
	SDL_Rect 		dst;
}					t_wall_texture;

typedef struct 		s_menu
{
	SDL_Texture		*texture;
	int 			in;
}					t_menu;

typedef struct 		s_texture
{
	SDL_Texture		*ground;
	SDL_Texture		*sky;
	SDL_Texture		*key;
}					t_texture;

// typedef struct 		s_sprite
// {
// 	int				visible;
// 	t_floatpoint	posi;
// 	// int				nb;
// }					t_sprite;


typedef struct	s_sp_lst
{

	// t_sprite		sp;
	int				id;
	int				visible;
	t_floatpoint	posi;
	struct s_sp_lst	*next;
}				t_sp_lst;


typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Window		*window;
	SDL_Renderer	*rend;
	t_camera		cam;
	t_texture		tex;
	t_sp_lst		*lst; // liste chainé de sprite


	int				sp_visible;
	t_floatpoint	sp_posi;
	t_menu			menu;
	SDL_Texture		*texture;
	t_wall_texture	wall;
	int				choose_inter;
}					t_context;

void				load_map(t_context *ct, const char *argv);
void				quit(char *msg, t_context *ct);
void				quit_nothing_to_free(char *msg);
void				free_map(t_context *ct);
int					init(t_context *ct, const char *argv);
void				loop(t_context *ct);
void				draw_background(t_context *ct);
double				convert_deg_to_rad(double angle);
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
void				init_valeur(t_context *ct);
void				draw_wall(t_context *ct);
void				choose_interface(t_context *ct);
void				print_menu(t_context *ct);
void				draw_line_wall(t_context *ct, float angle, int	x_pixel);
int					convert_mapdis_to_screendis(float distance, t_context *ct);
t_floatpoint		dda_return_posi(t_context *ct, float angle);
float				dda_return_distance(t_context *ct, float angle);
void				key_events_movein_2d(t_context *ct, Uint8 *state);
void				key_events_movein_3d(t_context *ct, Uint8 *state);
SDL_Rect			define_rect(int x, int y, int w, int h);
SDL_Texture			*init_texture(char *path, t_context *ct);
void				copy_texture_wall(float wall_point, t_context *ct, SDL_Texture *wall_texture);
void 				load_texture_wall(t_context *ct);
void				draw_ground(t_context *ct);
float				angle_limit(float angle);
void				draw_sprite_in_2d(t_context *ct);
void				draw_sprite_in_3d(t_context *ct);
void				load_texture_obj(t_context *ct);
void				hit_sprite(t_context *ct, SDL_Point to_int);
double				convert_rad_to_deg(double radian);








#endif
