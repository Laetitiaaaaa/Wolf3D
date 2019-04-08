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
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include <stdio.h>

# define XWIN 1000.0
# define YWIN 800.0
# define X_SKY 2000
# define Y_SKY 400
# define X_CUT_SKY 600
# define CUBESIZE 1.0 // cubesize must be 1, otherwise plan2d calcu will not work
# define NO_WALL -1.0
# define INITIAL 0
# define ANGLE 60
# define FIREWORKS_FRAMES 10
# define FIREWORKS_FRAME_TIME 200

typedef enum  		e_map_content
{
	EMPTY = 0,
	WALL_CUBE,
	CAM_CUBE,
	SPRITE_CUBE,
	TUYAU_CUBE = 6,
	MUSHROOM_CUBE = 7,
	KEY_CUBE = 8,
}					t_map_content;

typedef enum 		e_interface
{
	GAME = 0,
	MAP,
	INTERFACE_NB, // always leave it in the end
	FIREWORKS,
}					t_interface;

typedef enum 		e_enum_menu
{
	PLAY = 0,
	GUIDE,
	QUIT,
	OUT,
}					t_enum_menu;

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
	SDL_Texture		*mushroom;
	SDL_Texture		*words;
	SDL_Texture		*tuyau;
	SDL_Texture		*fireworks[FIREWORKS_FRAMES];
}					t_texture;

typedef struct	s_sp_lst
{

	int				id;
	float			distance;
	t_floatpoint	posi;
	struct s_sp_lst	*next;
}				t_sp_lst;

typedef struct s_sprite
{
	int				key_nb;
	int				mushroom_nb;
	int				door_nb;
}				t_sprite;


typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Window		*window;
	int 			xwin;
	int 			ywin;
	SDL_Renderer	*rend;
	t_camera		cam;
	t_texture		tex;
	t_sp_lst		*lst; // liste chainé de sprite
	t_sprite		sp;
	int				at_least_one_sprite;
	int				total_mushroom_nb;
	t_menu			menu;
	SDL_Texture		*texture;
	t_wall_texture	wall;
	int				choose_inter;
	int 			full_screen;
	Mix_Music		*music;
	Mix_Chunk		*chunk;
	int 			volume;
	int 			mute;
	TTF_Font		*font;
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
float 				set_neg_posi(t_context *ct, float angle);
void				init_valeur(t_context *ct);
void				draw_wall(t_context *ct);
void				print_menu(t_context *ct);
void				draw_line_wall(t_context *ct, float angle, int	x_pixel);
int					convert_mapdis_to_screendis(float distance, t_context *ct);
t_floatpoint		dda_return_posi(t_context *ct, float angle);
float				dda_return_distance(t_context *ct, float angle);
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
void				key_events(t_context *ct, Uint8 *state, unsigned int delta_time);
void				free_lst_sp(t_sp_lst *lst);
int					lst_new_sprite_check(t_sp_lst *lst, int id);
// void				init_struct(t_context *ct);
void				sprite_visible(t_context *ct, SDL_Point to_int, float angle);
void				loop_menu(t_context *ct);
void				copy_texture_menu(t_context *ct, char *path);
void				loop_guide(t_context *ct);
void				val_cam_neg_posi(t_context *ct, int a, int b);
void				common_actions(t_context *ct, Uint8 *state, SDL_Event event);
void				update_settings(t_context *ct);
void				limit_menu(t_context *ct);
t_sp_lst			*lst_fill(t_sp_lst *lst, int id, t_floatpoint posi, float distance);
t_sp_lst			*sort_list(t_sp_lst *lst);
void				draw_icon(t_context *ct);

#endif
