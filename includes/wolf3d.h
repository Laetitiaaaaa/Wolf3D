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

#ifndef wolf3d_H
# define wolf3d_H

# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libui/SDL2/SDL.h"
# define XWIN 900
# define YWIN 600

typedef struct 		s_pixel
{
	int				x;
	int				y;
}					t_pixel;

typedef struct		s_context
{
	SDL_Event		ev;
	SDL_Window		*window;
	SDL_Renderer	*rend;
}					t_context;


#endif
