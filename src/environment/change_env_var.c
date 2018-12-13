/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:37:35 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/12 18:49:57 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE

int			change_env_var(t_list **lst, char *name, char *newcontent)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp((((t_varenv *)((tmp)->content))->name), name) == 0)
			break;
		if ((tmp)->next == NULL)
			return (FALSE);
		(tmp) = (tmp)->next;
	}
	ft_strdel(&((t_varenv *)((tmp)->content))->content);
	((t_varenv *)((tmp)->content))->content = ft_strdup(newcontent);
	return (TRUE);
}