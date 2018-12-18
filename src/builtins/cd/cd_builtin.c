/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:26:03 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 03:37:41 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], OPTIONS_CD))
	{
		if (ops[pos] == 'L')
			*options |= OPT_L;
		else if (ops[pos] == 'P')
			*options |= OPT_P;
	}
	else
	{
		ft_printf("minishell: cd: illegal option -- %c\nusage: cd [-%s] [dir]\n"
			, ops[pos], OPTIONS_CD);
		return (FALSE);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

static int	malloc_error_set_errno(void)
{
	g_my_errno = FAIL_MALLOC;
	return (FALSE);
}

int		change_directory(char *pwd, char *oldpwd, int options)
{
	char cwd[PATH_MAX + 1];

	if (!check_path_errors(pwd))
		return (FALSE);
	if ((chdir(pwd)) < 0)
	{
		ft_printf("minishell: cd: %s: Permission denied\n", pwd);
		return (FALSE);
	}
	else
	{
		if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
			return (malloc_error_set_errno());
		if (options & OPT_P)
		{
			getcwd(cwd, PATH_MAX + 1);
			if (!(change_env_var(&g_env_lst, "PWD", cwd)))
				return (malloc_error_set_errno());
		}
		else
			if (!(change_env_var(&g_env_lst, "PWD", pwd)))
				return (malloc_error_set_errno());
	}
	return (TRUE);
}

static char 	*get_pwd_for_cd(int pos_args, char **args)
{
	t_varenv	*tmp;
	char 		*pwd;

	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
	{
		if (!(tmp = get_env_var_by_name("HOME")))
		{
			ft_printf("minishell: cd: HOME not set\n");
			return (FALSE);
		}
		pwd = get_final_path(tmp->content);
	}
	else if (ft_strcmp(args[pos_args], "-") == 0)
	{
		if (!(tmp = get_env_var_by_name("OLDPWD")))
		{
			ft_printf("minishell: cd: OLDPWD not set\n");
			return (FALSE);
		}
		pwd = get_final_path(tmp->content);
	}
	else
		pwd = get_final_path(args[pos_args]);
	return (pwd);
}

int		cd_builtin(char **args)
{
	char 	*oldpwd = NULL;
	char 	*pwd = NULL;
	int		pos_args;
	int		options;
	t_varenv *tmp;

	options = 0;
	pos_args = 0;
	options_parser(args, &options, &pos_args, set_options);
	if (!(tmp = get_env_var_by_name("PWD")))
	{
		change_env_var(&g_env_lst, "PWD", getcwd(NULL, sizeof(char *)));
		tmp = get_env_var_by_name("PWD");
	}
	oldpwd = tmp->content;
	if (!(pwd = get_pwd_for_cd(pos_args, args)))
		return (FALSE);
	if (!change_directory(pwd, oldpwd, options))
	{
		ft_strdel(&pwd);
		return (FALSE);
	}
	ft_strdel(&pwd);
	return (TRUE);
}
