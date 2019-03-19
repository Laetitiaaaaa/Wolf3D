/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:27:29 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/23 09:27:33 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	n = 0;
	if (needle[0] == 0)
	{
		return ((char*)(haystack));
	}
	while ((haystack[h] != 0) && (h < len))
	{
		while ((haystack[h] == needle[n]) && (h < len))
		{
			n++;
			h++;
			if (needle[n] == 0)
				return ((char*)(haystack + h - n));
		}
		h = h - n;
		n = 0;
		h++;
	}
	return (0);
}
