/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:26:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:42:36 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_builtin(char *arg, char ****commands)
{
	int		i;

	if (*commands)
	{
		i = -1;
		while ((*commands)[++i])
			ft_strtabdel((&(*commands)[i]));
		ft_memdel((void **)commands);
	}
	ft_strtabdel(&g_env_tab);
	ft_lstdel(&g_env_lst, del_env_var);
	if (arg)
		exit(ft_atoi(arg));
	else
		exit(EXIT_SUCCESS);
}
