/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:43:29 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/23 14:43:30 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		lenth(long long n)
{
	int		len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char		*convert(long long n, int len, char *ptr)
{
	int			count;

	count = 1;
	while (1)
	{
		ptr[len - count] = n % 10 + '0';
		n = n / 10;
		count++;
		if (n == 0)
			break ;
	}
	return (ptr);
}

char			*ft_itoa(int x)
{
	int			len;
	char		*ptr;
	int			neg;
	long long	n;

	n = x;
	len = lenth(n);
	ptr = (char*)malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (NULL);
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	ptr = convert(n, len, ptr);
	ptr[len] = '\0';
	if (neg == 1)
		ptr[0] = '-';
	return (ptr);
}
