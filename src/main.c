/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/01 03:22:57 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n%s", PROMPT);
	}
}

void		create_minimal_env(void)
{
	change_env_var(&g_env_lst, "SHLVL", "0");
	change_env_var(&g_env_lst, "PWD", getcwd(NULL, sizeof(char *)));
	change_env_var(&g_env_lst, "PATH", "/bin:/usr/bin");
}

void		manage_each_command(char ****commands)
{
	int		i;

	i = -1;
	while ((*commands)[++i])
	{
		if ((*commands)[i][0] == NULL)
			continue;
		if (!manage_builtins((*commands)[i], commands))
			exec_command((*commands)[i], g_env_tab);
	}
}

void		ft_minishell(void)
{
	char	*complete_cmd;
	char	***commands;
	int		i;

	commands = NULL;
	while (666)
	{
		ft_printf("%s", PROMPT);
		signal(SIGINT, catch_signal);
		if (!get_complete_command(&complete_cmd) || complete_cmd[0] == -1)
			exit_builtin("0", NULL);
		if (!(minishell_parser(complete_cmd, &commands)))
		{
			ft_strdel(&complete_cmd);
			continue;
		}
		ft_strdel(&complete_cmd);
		manage_each_command(&commands);
		i = -1;
		while (commands[++i])
			ft_strtabdel(&(commands[i]));
		ft_memdel((void **)&commands);
	}
}

int			main(int ac, char **av, char **environ)
{
	int			shlvl;
	char		*tmp;
	t_varenv	*envshlvl;

	(void)av;
	if (ac > 1)
		return (0);
	g_env_lst = NULL;
	g_env_tab = NULL;
	g_my_errno = 0;
	if (!env_tab_to_lst(&g_env_lst, environ))
		create_minimal_env();
	if (!(envshlvl = get_env_var_by_name("SHLVL")))
		shlvl = 0;
	else
		shlvl = ft_atoi(envshlvl->content);
	tmp = ft_itoa(shlvl + 1);
	change_env_var(&g_env_lst, "SHLVL", tmp);
	ft_strdel(&tmp);
	env_lst_to_tab(&g_env_lst, &g_env_tab);
	ft_minishell();
	return (EXIT_SUCCESS);
}
