/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:37:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/30 02:15:03 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_var(t_list **lst, char *name, char *newcontent)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strequ((((t_varenv *)((tmp)->content))->name), name))
			break ;
		if ((tmp)->next == NULL)
		{
			if (!add_env_var(lst, name, newcontent))
				return (FALSE);
			return (TRUE);
		}
		tmp = (tmp)->next;
	}
	if (((t_varenv *)((tmp)->content))->content)
		ft_strdel(&((t_varenv *)((tmp)->content))->content);
	if (newcontent)
		((t_varenv *)((tmp)->content))->content = ft_strdup(newcontent);
	else
		((t_varenv *)((tmp)->content))->content = ft_strdup("");
	if (!((t_varenv *)((tmp)->content))->content)
		return (FALSE);
	return (TRUE);
}

int			change_env_var(t_list **lst, char *name, char *newcontent)
{
	if (!name)
		return (FALSE);
	if (!(*lst))
	{
		if (!add_env_var(lst, name, newcontent))
			return (FALSE);
		return (TRUE);
	}
	if (!update_env_var(lst, name, newcontent))
		return (FALSE);
	return (TRUE);
}
