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

void				check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if ((line[i] != ' ') && (line[i] != '-')
			&& ((line[i] < '0') || (line[i] > '9')))
		{
			quit_nothing_to_free("content of map file is not right");
		}
		i++;
	}
}

int					*aatoii(char **pptr, t_context *ct)
{
	int		*tab;
	int		j;

	ct->mpp.x = 0;
	while (pptr[ct->mpp.x] != 0)
		(ct->mpp.x)++;
	if (!(tab = (int*)malloc((ct->mpp.x) * sizeof(int))))
		quit("malloc one line of map failed", ct);
	ct->mpp.x = 0;
	while (pptr[ct->mpp.x] != 0)
	{
		tab[ct->mpp.x] = ft_atoi(pptr[ct->mpp.x]);
		(ct->mpp.x)++;
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

void				stock_map(int fd, t_context *ct)
{
	char	*line;
	int		temp;
	int		ret;

	temp = 0;
	ct->mpp.y = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		ret == -1 ?	quit("error with get_next_line()", ct) : 0;
		if ((ct->mpp.y == 0) && (ret == 0))
			quit_nothing_to_free("map file shold not be empty");
		if (ret == 0)
			break ;
		check_map_line(line);
		ct->mpp.map[ct->mpp.y] = aatoii(ft_strsplit(line, ' '), ct);
		if (ct->mpp.y == 0)
			temp = ct->mpp.x;
		else if (ct->mpp.x != temp)
			quit("error:the LENGTH OF EACH LINE SHOULD BE THE SAME", ct);
		ct->mpp.y++;
		ct->mpp.y >= 499 ? quit("map too big", ct) : 0;
		free(line);
		line = NULL;
	}
}

void				load_map(t_context *ct, const char *argv)
{
	int		fd;

	ct->mpp.map = (int**)malloc(sizeof(int*) * 500);
	if (ct->mpp.map == NULL)
		quit_nothing_to_free("failed to malloc for ct->mpp.map");
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		quit_nothing_to_free("error with open() in load_map");
	stock_map(fd, ct);
	close(fd);
}
