/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:27:31 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/21 19:27:33 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (src[i] == 0)
		{
			while (i < n)
			{
				dst[i] = 0;
				i++;
			}
			return (dst);
		}
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
