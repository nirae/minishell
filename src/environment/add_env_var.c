/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:15:53 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/17 21:22:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_env_var(t_list **lst, char *name, char *content)
{
	t_list	*tmplst;

	if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
		return (FALSE);
	if (!(tmplst->content = create_varenv(name, content)))
		return (FALSE);
	if (!(*lst))
		(*lst) = tmplst;
	else
		ft_lstaddend(lst, tmplst);
	return (TRUE);
}
