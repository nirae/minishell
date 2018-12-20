/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nico <Nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:00:13 by Nico              #+#    #+#             */
/*   Updated: 2018/12/20 03:02:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			remove_env_var(t_list **lst, char *name)
{
	t_list	*prev;
	t_list	*tmp;

	tmp = *lst;
	if (tmp && ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
	{
		prev = tmp;
		*lst = tmp->next;
		ft_lstdelone(&prev, del_env_var);
		return (TRUE);
	}
	while (tmp)
	{
		if (tmp->next
			&& ft_strcmp(((t_varenv *)(tmp->next->content))->name, name) == 0)
		{
			prev = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(&prev, del_env_var);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}
