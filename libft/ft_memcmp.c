/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:05:18 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/22 10:05:19 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i])
			i++;
		else
			return ((int)(((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]));
	}
	return (0);
}
