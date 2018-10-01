/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:20:53 by ndubouil          #+#    #+#             */
/*   Updated: 2017/12/09 12:10:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lsti(t_list *lst, int i)
{
	int j;

	if (lst == NULL || i > ft_lstlen(lst) || i < 0)
		return (NULL);
	j = 0;
	while (j < i)
	{
		lst = lst->next;
		j++;
	}
	return (lst);
}
