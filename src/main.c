/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 04:38:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void     ft_getleaks(char *str)
// {
//        system("leaks minishell");
//        ft_printf("%s\n", str);
//        getchar();
// }

void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n%s", PROMPT);
	}
}


int		create_my_env(t_list **lst, char **environ)
{
	int		i;
	t_list	*tmplst;
	char	**env;
	int		pos;

	if (environ[0] == NULL)
	{
		// if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
		// 	ft_printf("lstnew a foire\n");
		// tmplst->content = create_varenv("SHELL", "minishell");
		// *lst = tmplst;

		return (FALSE);
	}
	i = 0;
	while (environ[i])
	{
		// a proteger
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			ft_printf("lstnew a foire\n");
		if (!(env = ft_strsplit(environ[i], '=')))
		 	ft_printf("strsplit a foire\n");
		pos = ft_strpos(environ[i], '=');
		// tmplst->content = create_varenv(env[0], env[1]);
		tmplst->content = create_varenv(env[0], &environ[i][pos + 1]);
		if (!(*lst))
			*lst = tmplst;
		else
			ft_lstadd(lst, tmplst);
		ft_strtabdel(&env);
		i++;
	}
	return (TRUE);
}

int			remove_one(t_list **lst, char *name)
{
	t_list	*prev;
	t_list	*tmp;


	tmp = *lst;
	if (tmp && ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
	{
		prev = tmp;
		*lst = tmp->next;
		ft_lstdelone(&prev, del_env_var);
		return (1);
	}
	while(tmp)
	{
		if (tmp->next && ft_strcmp(((t_varenv *)(tmp->next->content))->name, name) == 0)
		{
				prev = tmp->next;
				tmp->next = tmp->next->next;
				ft_lstdelone(&prev, del_env_var);
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		print_lstenv(t_list *lst)
{
	ft_printf("%s=%s\n", ((t_varenv *)(lst->content))->name, ((t_varenv *)(lst->content))->content);
}

void 		reset_env_tab(void)
{
	ft_strtabdel(&g_env_tab);
	env_lst_to_tab(&g_env_lst, &g_env_tab);
}

int			manage_builtins(char **command)
{
	int i;

	if (ft_strcmp(command[0], "exit") == 0)
		exit_builtin(command[1]);
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		if (!cd_builtin(command) && g_my_errno == FAIL_MALLOC)
			exit_builtin("1");
		reset_env_tab();
	}
	else if (ft_strcmp(command[0], "env") == 0)
		env_builtin(command);
	else if (ft_strcmp(command[0], "setenv") == 0)
	{
		if (command[1])
		{
			change_env_var(&g_env_lst, command[1], command[2]);
			reset_env_tab();
		}
		else
		{
			i = -1;
			while (g_env_tab[++i])
				ft_printf("%s\n", g_env_tab[i]);
		}
	}
	else if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		remove_one(&g_env_lst, command[1]);
		reset_env_tab();
	}
	else if (ft_strcmp(command[0], "echo") == 0)
		echo_builtin(command);
	else
		return (FALSE);
	return (TRUE);
}

int			main(int ac, char **av, char **environ)
{
	char	*strrr;
	char	***command = NULL;
	int		y;
	int z;
	int	shlvl;

	(void)ac;
	(void)av;
	g_env_lst = NULL;
	g_env_tab = NULL;
	g_my_errno = 0;
	// copie de environ
	if (!create_my_env(&g_env_lst, environ))
	{
		change_env_var(&g_env_lst, "SHLVL", "0");
		change_env_var(&g_env_lst, "PWD", getcwd(NULL, sizeof(char *)));
		change_env_var(&g_env_lst, "PATH", "/bin:/usr/bin");
	}
	shlvl = ft_atoi(get_env_var_by_name("SHLVL")->content);
	change_env_var(&g_env_lst, "SHLVL", ft_itoa(shlvl + 1));
	// env_paths = get_env_paths(g_env_lst);
	env_lst_to_tab(&g_env_lst, &g_env_tab);
	/*
	** Boucle infinie du programme
	*/
	while (666)
	{
		// Surveille le signal de CTRL C
		signal(SIGINT, catch_signal);
		// Affiche le prompt
		ft_printf(PROMPT);
		get_complete_command(&strrr);
		if (!strrr)
			exit(0);
		if (!(minishell_parser(strrr, &command)))
		{
			ft_printf("minishell: parsing error\n");
			ft_strdel(&strrr);
			continue;
		}
		ft_strdel(&strrr);
		y = -1;
		while (command[++y])
		{
			if (command[y][0] == NULL)
				continue;
			if (manage_builtins(command[y]))
				continue;
			exec_command(command[y], g_env_tab);
		}
		// FREE command
		z = -1;
		while (command[++z])
			ft_strtabdel(&(command[z]));
	}
	return (EXIT_SUCCESS);
}
