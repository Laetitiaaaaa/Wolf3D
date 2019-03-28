/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:17:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/25 15:17:16 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void				quit_map(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void					check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if ((line[i] != ' ') && (line[i] != '-')
			&& ((line[i] < '0') || (line[i] > '9')))
		{
			quit_map("content of map file is not right");
		}
		i++;
	}
}

void					check_map(const char *argv, t_map_params *mpp)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		quit_map("map load failed, error with open()");
	mpp->y = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			quit_map("error with get_next_line()");
		if ((mpp->y == 0) && (ret == 0))
			quit_map("map file shold not be empty");
		if (ret == 0)
			break ;
		check_map_line(line);
		mpp->y++;
		free(line);
		line = NULL;
	}
	close(fd);
}

int					*aatoii(char **pptr, int *mppx)
{
	int		*tab;
	int		j;

	*mppx = 0;
	while (pptr[*mppx] != 0)
	{
		(*mppx)++;
	}
	if (!(tab = (int*)malloc((*mppx) * sizeof(int))))
		return (0);
	*mppx = 0;
	while (pptr[*mppx] != 0)
	{
		tab[*mppx] = ft_atoi(pptr[*mppx]);
		(*mppx)++;
	}
	j = 0;
	while (pptr[j] != NULL)
	{
		free(pptr[j]);
		j++;
	}
	free(pptr);
	return (tab);
}

void		free_map(t_context *ct)
{
	int		i;

	i = 0;
	while (i < ct->mpp.y)
	{
		free(ct->mpp.map[i]);
		i++;
	}
	free(ct->mpp.map);

}

void		stock_map(int fd, t_context *ct)
{
	char			*line;
	int				temp;
	int				ret;

	temp = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
		{
			free(ct->mpp.map);
			quit_map("error with get_next_line()");
		}
		if (ret == 0)
			break ;
		ct->mpp.map[ct->mpp.y] = aatoii(ft_strsplit(line, ' '), &(ct->mpp.x));
		if (ct->mpp.y == 0)
			temp = ct->mpp.x;
		else if (ct->mpp.x != temp)
		{
			free_map(ct);
			free(line);
			quit_map("error:the LENGTH OF EACH LINE SHOULD BE THE SAME");
		}
		ct->mpp.y++;
		free(line);
		line = NULL;
	}
}


int		load_map(t_context *ct, const char *argv)
{
	int				fd;

	check_map(argv, &(ct->mpp));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		quit_map("error with open() in load_map");
	ct->mpp.map = (int**)malloc(sizeof(int*) * ct->mpp.y);
	if (ct->mpp.map == NULL)
		quit_map("failed to malloc for ct->mpp.map");
	ct->mpp.y = 0;
	stock_map(fd, ct);
	close(fd);
	return (0);
}
