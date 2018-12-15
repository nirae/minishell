/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:15:53 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/15 00:27:00 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		add_env_var(char *name, char *content)
{
	t_list	*tmplst;

	// a proteger
	tmplst = ft_lstnew(NULL, sizeof(t_varenv *));
	tmplst->content = create_varenv(name, content);
	ft_lstaddend(&g_env_lst, tmplst);
	return (TRUE);
}
