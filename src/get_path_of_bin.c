/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_of_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 03:09:35 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/30 02:22:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**get_env_paths(t_list *lst)
{
	t_list	*tmp;
	char	**env_paths;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp((((t_varenv *)(tmp->content))->name), "PATH") == 0)
			break ;
		if (tmp->next == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	env_paths = ft_strsplit(((t_varenv *)(tmp->content))->content, ':');
	return (env_paths);
}

static char		*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/' || name[0] == '.')
		return (ft_strdup(name));
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

static char		*check_file_exist_in_path(struct stat *st, char **cmp_path,
					char ***env_paths, char *path)
{
	if (access(*cmp_path, X_OK) == 0)
	{
		stat(*cmp_path, st);
		if (S_ISREG(st->st_mode))
		{
			ft_strtabdel(env_paths);
			return (*cmp_path);
		}
		else if (S_ISDIR(st->st_mode) && path[0])
		{
			ft_printf("minishell: %s: is a directory\n", path);
			ft_strdel(cmp_path);
			ft_strtabdel(env_paths);
			return (NULL);
		}
		ft_strtabdel(env_paths);
		return (*cmp_path);
	}
	else
	{
		ft_printf("minishell: %s: Permission denied\n", path);
		ft_strtabdel(env_paths);
		ft_strdel(cmp_path);
		return (NULL);
	}
}

static char		*search_path(char ***env_paths, char *path)
{
	int				i;
	char			*cmp_path;
	struct stat		st;

	i = -1;
	while ((*env_paths)[++i])
	{
		cmp_path = get_complete_path((*env_paths)[i], path);
		if (access(cmp_path, F_OK) == 0)
			return(check_file_exist_in_path(&st, &cmp_path, env_paths, path));
		else
		{
			if (!(*env_paths)[i + 1])
			{
				ft_printf("minishell: command not found: %s\n", path);
				ft_strdel(&cmp_path);
				return (NULL);
			}
		}
		ft_strdel(&cmp_path);
	}
	return (NULL);
}

char			*get_path_of_bin(char *path)
{
	char		**env_paths;
	struct stat	st;
	char		*result;
	char		*new_path;

	stat(path, &st);
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			if (S_ISREG(st.st_mode) && (path[0] == '.' || path[0] == '/'))
				return (ft_strdup(path));
		}
		else
			return (perm_denied(path));
	}
	env_paths = get_env_paths(g_env_lst);
	if (!env_paths)
		return (cmd_not_found(path));
	new_path = search_path(&env_paths, path);
	result = ft_strdup(new_path);
	ft_strdel(&new_path);
	ft_strtabdel(&env_paths);
	return (result);
}
