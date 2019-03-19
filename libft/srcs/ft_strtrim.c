/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:02:55 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/26 13:02:58 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		isspace(char c)
{
	return ((c == ' ') || (c == '\n') || (c == '\t'));
}

static int		tell_start(char const *s)
{
	int		start;

	start = 0;
	while (isspace(s[start]) && s[start] != 0)
	{
		start++;
	}
	return (start);
}

static	int		tell_end(char const *s)
{
	int		end;

	end = ft_strlen(s) - 1;
	while (isspace(s[end]) && (end > 0))
	{
		end--;
	}
	return (end);
}

char			*ft_strtrim(char const *s)
{
	char	*ptr;
	int		start;
	int		end;
	int		i;
	int		trimlen;

	if (s == 0)
		return (0);
	start = tell_start(s);
	end = tell_end(s);
	trimlen = end - start + 1;
	trimlen = trimlen > 0 ? trimlen : 0;
	ptr = (char *)malloc((trimlen + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < trimlen)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[trimlen] = '\0';
	return (ptr);
}
