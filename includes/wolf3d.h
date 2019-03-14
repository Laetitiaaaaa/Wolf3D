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

# define XWIN 900
# define YWIN 600

typedef struct		s_map_params
{
	int				x;
	int				y;
	int				ret;
	float			d;
	int				**map;
	int				z_max;
	int				z_min;
}					t_map_params;

typedef struct 		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_context
{
	t_map_params	mpp;
	SDL_Event		ev;
	SDL_Window		*window;
	SDL_Renderer	*rend;
}					t_context;

int					load_map(t_context *ct, const char *argv);
int					init(t_context *ct, const char *argv);


#endif
