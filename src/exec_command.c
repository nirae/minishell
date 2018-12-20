/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 02:21:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:05:09 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal_kill(int signal)
{
	if (signal == SIGINT)
	{
		kill(g_pid, SIGTERM);
	}
}

static char		**get_env_paths(t_list *lst)
{
	t_list	*tmp;
	char	**env_paths;

	tmp = lst;
	while (lst)
	{
		if (ft_strcmp((((t_varenv *)(tmp->content))->name), "PATH") == 0)
			break;
		if (tmp->next == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	env_paths = ft_strsplit(((t_varenv *)(tmp->content))->content, ':');
	return (env_paths);
}

/*
**	Return the complete path of a file name or exit if malloc failed
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/' || name[0] == '.')
		return (name);
	if (parent == NULL)
	{
		if (!(result = ft_strjoin("./", name)))
			error();
		return (result);
	}
	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			error();
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			error();
	}
	if (!(result = ft_strjoin(tmp, name)))
		error();
	ft_strdel(&tmp);
	return (result);
}

static char 	*get_path_of_bin(char *path)
{
	char **env_paths;
	int i;
	struct stat st;
	char *cmp_path;

	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			stat(path, &st);
			if (S_ISREG(st.st_mode) && (path[0] == '.' && path[1] == '/'))
				return (path);
		}
		else
		{
			ft_printf("minishell: %s: Permission denied\n", path);
			return (NULL);
		}
	}
	env_paths = get_env_paths(g_env_lst);
	if (!env_paths)
	{
		ft_printf("minishell: PATH not set\n");
		return (NULL);
	}
	i = -1;
	while (env_paths[++i])
	{
		cmp_path = get_complete_path(env_paths[i], path);
		if (access(cmp_path, F_OK) == 0)
		{
			if (access(cmp_path, X_OK) == 0)
			{
				stat(cmp_path, &st);
				if (S_ISREG(st.st_mode))
				{
					ft_strtabdel(&env_paths);
					return (cmp_path);
				}
				else if (S_ISDIR(st.st_mode) && path[0])
				{
					ft_printf("minishell: %s: is a directory\n", path);
					ft_strtabdel(&env_paths);
					// ft_strdel(&cmp_path);
					return (NULL);
				}
				ft_strtabdel(&env_paths);
				return (cmp_path);
			}
			else
			{
				ft_printf("minishell: %s: Permission denied\n", path);
				ft_strtabdel(&env_paths);
				ft_strdel(&cmp_path);
				return (NULL);
			}
		}
		else
		{
			// Si c'etait le dernier -> pas trouve
			if (!env_paths[i + 1])
			{
				ft_printf("minishell: command not found: %s\n", path);
				ft_strtabdel(&env_paths);
				ft_strdel(&cmp_path);
				break;
			}
		}
		ft_strdel(&cmp_path);
	}
	ft_strtabdel(&env_paths);
	return (NULL);
}

int			exec_command(char **command, char **env)
{
	int status;
	char *final_path;

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
	ft_strdel(&final_path);
	return (TRUE);
}
