/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 22:29:33 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:40:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*ft_lstcpy(t_list *src, t_list **dest)
{
	t_list		*tmp;
	t_list		*tmplst;
	char		*name;
	char		*content;

	(*dest) = NULL;
	tmp = src;
	while (tmp)
	{
		tmplst = ft_lstnew(NULL, sizeof(t_varenv *));
		name = ft_strdup(((t_varenv*)(tmp->content))->name);
		content = ft_strdup(((t_varenv*)(tmp->content))->content);
		if (!name || !content || !tmplst)
			return (NULL);
		if (!(tmplst->content = create_varenv(name, content)))
			return (NULL);
		if (!(*dest))
			(*dest) = tmplst;
		else
			ft_lstaddend(dest, tmplst);
		tmp = tmp->next;
		ft_strdel(&name);
		ft_strdel(&content);
	}
	return (*dest);
}
