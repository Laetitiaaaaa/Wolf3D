/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:08:52 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/23 18:08:56 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*s2;
	int		i;

	if (s == 0)
		return (0);
	s2 = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (s2 == 0)
	{
		return (0);
	}
	i = 0;
	while (s[i] != 0)
	{
		s2[i] = (*f)(s[i]);
		i++;
	}
	s2[i] = 0;
	return (s2);
}
