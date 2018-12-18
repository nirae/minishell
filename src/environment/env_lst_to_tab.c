/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:28:18 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 21:53:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	del_tab(char ***tab)
{
	int		i;

	i = 0;
	while((*tab)[i++])
		ft_strdel(&(*tab)[i]);
	*tab = NULL;
}

static int		cpy_tab(t_list *lst, char ***tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (lst)
	{
		if (!((*tab)[i] = ft_strjoin(((t_varenv *)((lst)->content))->name
			, "=")))
			return (FALSE);
		if (((t_varenv *)((lst)->content))->content)
		{
			tmp = (*tab)[i];
			if (!((*tab)[i] = ft_strjoin((*tab)[i]
				, ((t_varenv *)((lst)->content))->content)))
				return (FALSE);
			ft_strdel(&tmp);
		}
		lst = lst->next;
		i++;
	}
	(*tab)[i] = NULL;
	return (TRUE);
}

int		env_lst_to_tab(t_list **lst, char ***tab)
{
	t_list	*node;

	if (*tab != NULL)
		del_tab(tab);
	node = *lst;
	if (*tab == NULL)
		if (!(*tab = (char **)ft_memalloc(sizeof(char *) * (ft_lstlen(*lst) + 1))))
			return (FALSE);
	if (node != NULL)
		if (!cpy_tab(node, tab))
			return (FALSE);
	return (TRUE);
}
