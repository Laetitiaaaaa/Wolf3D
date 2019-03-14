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

int					check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if ((line[i] != ' ') && (line[i] != '-')
			&& ((line[i] < '0') || (line[i] > '9')))
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int					check_map(const char *argv, t_context *ct)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		quit("open fd failed");
	ct->mpp->y = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		(ret == -1) ? quit("get_next_line failed") : 0;
		if ((ct->mpp->y == 0) && (ret == 0))
			quit("map file should not be empty");
		if (ret == 0)
			break ;
		ret = check_map_line(line);
		if (ret == -1)
			quit("content of map file is not right");
		ct->mpp->y++;
		free(line);
		line = 0;
	}
	close(fd);
	return (0);
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

t_map_params		stock_map(int fd, t_map_params mpp)
{
	char			*line;
	int				temp;
	int				ret;

	temp = 0;
	while (1)
	{
		ret = get_next_line(fd, &line);
		(ret == -1) ? quit("get_next_line failed") : 0;
		(ret == 0) ? break : 0;
		mpp.map[mpp.y] = aatoii(ft_strsplit(line, ' '), &mpp.x);
		if (mpp.y == 0)
			temp = mpp.x;
		else if (mpp.x != temp)
		{
			quit("error:the length of each line should be the same");
		}
		mpp.y++;
		free(line);
		line = NULL;
	}
	return (mpp);
}


int		load_map(t_context *ct, const char *argv)
{
	int				fd;
	int				ret;

	ret = check_map(argv, &(ct->mpp));
	if ((ret == -1) || (ret == -2) || (ret == -3))
		return (ret);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	ct->mpp.map = (int**)malloc(sizeof(int*) * ct->mpp.y);
	if (ct->mpp.map == NULL)
		return (-1);
	ct->mpp.y = 0;
	ct->mpp = stock_map(fd, ct->mpp);
	close(fd);
	return (0);
}
