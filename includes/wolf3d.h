/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:06:38 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/14 09:08:52 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"
# include <stdio.h>

# define XWIN 900
# define YWIN 600

typedef enum 		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef struct		s_map_params
{
	int				x;  // x and y are the number of points  for map 42, x = 10 y = 11
	int				y;
	int				ret;
	float			d;
	int		**map;
//	int				z_max;
//	int				z_min;
}					t_map_params;

typedef struct 		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Window		*window;
	SDL_Renderer	*rend;
}					t_context;

int					load_map(t_context *ct, const char *argv);
int					init(t_context *ct, const char *argv);
void				quit(char *msg, t_context *ct);
void				loop(t_context *ct);


#endif
