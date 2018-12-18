/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_by_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:56:05 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 21:55:18 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varenv		*get_env_var_by_name(char *name)
{
	t_list	*tmp;

	tmp = g_env_lst;
	while(tmp)
	{
		if (ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
			return (((t_varenv *)(tmp->content)));
		tmp = tmp->next;
	}
	return (NULL);
}
