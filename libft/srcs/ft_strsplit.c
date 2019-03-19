/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:49:21 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/26 12:49:40 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*to_zero(char *s, char c)
{
	int		x;

	x = 0;
	while (s[x])
	{
		if (s[x] == c)
		{
			s[x] = '\0';
		}
		x++;
	}
	return (s);
}

static char		**fill_array(char const *s, char *s1, char **pptr)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (x < ft_strlen(s))
	{
		while (s1[x] != '\0')
		{
			pptr[y] = (char*)malloc(sizeof(char) * (ft_strlen(s1 + x) + 1));
			if (!pptr[y])
				return (0);
			ft_strcpy(pptr[y], s1 + x);
			y++;
			x = x + ft_strlen(s1 + x);
		}
		x++;
	}
	pptr[y] = 0;
	return (pptr);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**pptr;
	int		word_nbr;
	char	*s1;

	if (!s)
		return (0);
	word_nbr = ft_word_nbr_counter(s, c);
	s1 = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s1)
		return (0);
	s1 = to_zero(ft_strcpy(s1, s), c);
	pptr = (char**)malloc(sizeof(char*) * (word_nbr + 1));
	if (pptr == 0)
		return (0);
	pptr = fill_array(s, s1, pptr);
	free(s1);
	return (pptr);
}
