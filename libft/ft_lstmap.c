/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:33:59 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/23 21:31:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first_elem;
	t_list	*new_list;
	t_list	*temp;

	if (lst == NULL)
		return (0);
	if (!(first_elem = ft_lstnew(lst->content, lst->content_size)))
		return (0);
	first_elem = f(first_elem);
	new_list = first_elem;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(temp = ft_lstnew(lst->content, lst->content_size)))
			return (0);
		temp = f(temp);
		new_list->next = temp;
		new_list = new_list->next;
		lst = lst->next;
	}
	return (first_elem);
}
