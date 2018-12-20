/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nico <Nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:58:16 by Nico              #+#    #+#             */
/*   Updated: 2018/12/20 02:43:19 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			reset_env_tab(void)
{
	ft_strtabdel(&g_env_tab);
	if (!env_lst_to_tab(&g_env_lst, &g_env_tab))
		exit_builtin("1", NULL);
}

int					manage_builtins(char **command, char ****commands)
{
	if (ft_strequ(command[0], "exit"))
		exit_builtin(command[1], commands);
	else if (ft_strequ(command[0], "cd"))
	{
		if (!cd_builtin(command) && g_my_errno == FAIL_MALLOC)
			exit_builtin("1", NULL);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "env"))
		env_builtin(command);
	else if (ft_strequ(command[0], "setenv"))
	{
		setenv_builtin(command);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "unsetenv"))
	{
		unsetenv_builtin(command);
		reset_env_tab();
	}
	else if (ft_strequ(command[0], "echo"))
		echo_builtin(command);
	else
		return (FALSE);
	return (TRUE);
}
