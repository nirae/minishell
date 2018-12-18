/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:28:18 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 02:28:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_lst_to_tab(t_list **lst, char ***tab)
{
	int		i;
	char	*tmp;
	t_list	*node;

	if (*tab != NULL)
	{
		i = 0;
		while((*tab)[i++])
			ft_strdel(&(*tab)[i]);
		*tab = NULL;
	}
	node = *lst;
	if (*tab == NULL)
		if (!(*tab = (char **)ft_memalloc(sizeof(char *) * (ft_lstlen(*lst) + 1))))
			return;
	if (node != NULL)
	{
		i = 0;
		while (node)
		{
			if (!((*tab)[i] = ft_strjoin(((t_varenv *)((node)->content))->name, "=")))
				ft_printf("strjoin fail\n");
			if (((t_varenv *)((node)->content))->content)
			{
				tmp = (*tab)[i];
				if (!((*tab)[i] = ft_strjoin((*tab)[i], ((t_varenv *)((node)->content))->content)))
					ft_printf("strjoin fail\n");
				ft_strdel(&tmp);
			}
			(node) = (node)->next;
			i++;
		}
		(*tab)[i] = NULL;
	}
}
