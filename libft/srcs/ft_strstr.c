/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:05:51 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/22 17:05:53 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		h;
	int		n;

	h = 0;
	n = 0;
	if (needle[0] == 0)
	{
		return ((char*)(haystack));
	}
	while (haystack[h] != 0)
	{
		while (haystack[h] == needle[n])
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
