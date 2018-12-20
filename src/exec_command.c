/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:21:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 03:58:15 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		catch_signal_kill(int signal)
{
	if (signal == SIGINT)
	{
		kill(g_pid, SIGTERM);
	}
}

int				exec_command(char **command, char **env)
{
	int		status;
	char	*final_path;

	if (!command[0][0] || !(final_path = get_path_of_bin(command[0])))
		return (FALSE);
	g_pid = fork();
	if (g_pid == 0)
		execve(final_path, command, env);
	else if (g_pid < 0)
		ft_printf("fail\n");
	else if (g_pid > 0)
	{
		signal(SIGINT, catch_signal_kill);
		waitpid(g_pid, &status, 0);
	}
	if (final_path[0] != '.')
		ft_strdel(&final_path);
	return (TRUE);
}
