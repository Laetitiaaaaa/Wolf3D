/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:46:57 by jleblond          #+#    #+#             */
/*   Updated: 2018/11/26 12:47:09 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*ret;
	t_list	*ptr;

	ret = NULL;
	while (lst != NULL)
	{
		if (ret == NULL)
		{
			ret = ft_lstnew(lst->content, lst->content_size);
			ptr = ret;
		}
		else
		{
			ptr->next = ft_lstnew(lst->content, lst->content_size);
			ptr = ptr->next;
		}
		lst = lst->next;
	}
	return (ret);
}
