/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 17:50:03 by ndubouil          #+#    #+#             */
/*   Updated: 2017/12/05 22:59:19 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *temp;
	t_list *list;

	if (new != NULL)
	{
		temp = *alst;
		list = *alst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		*alst = list;
	}
}
