/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:37:35 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 03:51:21 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			change_env_var(t_list **lst, char *name, char *newcontent)
{
	t_list	*tmp;

	if (!name)
		return (FALSE);
	if (!(*lst))
	{
		add_env_var(lst, name, newcontent);
		return (TRUE);
	}
	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp((((t_varenv *)((tmp)->content))->name), name) == 0)
			break;
		if ((tmp)->next == NULL)
		{
			if (!add_env_var(lst, name, newcontent))
				return (FALSE);
			return (TRUE);
		}
		tmp = (tmp)->next;
	}
	ft_strdel(&((t_varenv *)((tmp)->content))->content);
	if (!(((t_varenv *)((tmp)->content))->content = ft_strdup(newcontent)))
		return (FALSE);
	return (TRUE);
}
