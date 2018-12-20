/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:33:08 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:37:41 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (parent == NULL || name == NULL)
		return (NULL);
	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
	{
		if (!(tmp = ft_strdup(&name[2])))
			return (NULL);
		ft_strdel(&name);
		name = tmp;
	}
	if (parent[ft_strlen(parent) - 1] == '/')
		tmp = ft_strdup(parent);
	else
		tmp = ft_strjoin(parent, "/");
	if (!tmp)
		return (NULL);
	if (!(result = ft_strjoin(tmp, name)))
		return (NULL);
	ft_strdel(&tmp);
	return (result);
}

static void		*malloc_error_set_errno(void)
{
	g_my_errno = FAIL_MALLOC;
	return (NULL);
}

static void		clean_absolute_path(char **path)
{
	char **pwd_tab;
	char *str;

	if ((*path)[0] == '/' && (*path)[1] != '.')
	{
		if (!(pwd_tab = ft_strsplit(*path, '/')))
			return ;
		if (!(str = ft_strjointab(pwd_tab, '/')))
		{
			ft_strtabdel(&pwd_tab);
			return ;
		}
		ft_strtabdel(&pwd_tab);
		ft_strdel(path);
		*path = ft_strdup(str);
		ft_strdel(&str);
	}
}

char			*get_final_path(char **path)
{
	char **arg_tab;
	char **pwd_tab;
	char *pwd;
	char *str;

	if (!(pwd = get_env_var_by_name("PWD")->content))
		getcwd(pwd, sizeof(char *));
	clean_absolute_path(path);
	if ((*path)[0] == '/' && (*path)[1] != '.')
		return (ft_strdup(get_complete_path(pwd, *path)));
	if (!(arg_tab = ft_strsplit(*path, '/')))
		return (malloc_error_set_errno());
	if (!(pwd_tab = ft_strsplit(pwd, '/')))
		return (malloc_error_set_errno());
	if (!build_pwd_tab(&arg_tab, &pwd_tab, ft_stringtab_len(pwd_tab)))
	{
		ft_strtabdel(&arg_tab);
		ft_strtabdel(&pwd_tab);
		return (NULL);
	}
	if (!(str = ft_strjointab(pwd_tab, '/')))
		return (malloc_error_set_errno());
	ft_strtabdel(&arg_tab);
	ft_strtabdel(&pwd_tab);
	return (str);
}
