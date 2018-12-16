/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:26:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/16 18:14:17 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_builtin(char *arg)
{
	ft_strtabdel(&g_env_tab);
	ft_lstdel(&g_env_lst, del_env_var);
	// FREE L'ENV AVANT
	if (arg)
		exit(ft_atoi(arg));
	else
		exit(EXIT_SUCCESS);
}
