/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:20:42 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/26 13:20:44 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*previous;
	t_list	*next;
	t_list	*ptr;

	ptr = ft_lstcpy(lst);
	ret = NULL;
	previous = NULL;
	next = NULL;
	while (ptr != NULL)
	{
		next = ptr->next;
		ptr = (*f)(ptr);
		ptr->next = next;
		if (previous != NULL)
			previous->next = ptr;
		if (ret == NULL)
		{
			ret = ptr;
		}
		previous = ptr;
		ptr = ptr->next;
	}
	return (ret);
}
