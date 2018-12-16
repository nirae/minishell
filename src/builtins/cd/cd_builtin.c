/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:26:03 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/16 21:14:04 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void     ft_getleaks(char *str)
// {
//        system("leaks minishell");
//        ft_printf("%s\n", str);
//        getchar();
// }

/*******************************************************************************
**							OPTIONS
*******************************************************************************/

/*
**	Check if the option is valid, return TRUE or FALSE
*/

static int		is_valid_option(char c)
{
	if (!ft_isprint(c) || (!ft_strchr(OPTIONS_CD, c) && c != ' ') || !c)
		return (FALSE);
	return (TRUE);
}

/*
**	Set the good option in the env struct. Check the options recursively
**	- If an option is not valid (check with is_valid_option()), print the error
**	and exit the program with EXIT_FAILURE;
*/

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos]))
	{
		if (ops[pos] == 'L')
			*options |= OPT_L;
		else if (ops[pos] == 'P')
			*options |= OPT_P;
	}
	else
	{
		ft_printf("minishell: cd: illegal option -- %c\nusage: cd [-%s] [file ...]\n"
			, ops[pos], OPTIONS_CD);
		return (FALSE);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

/*
**	The parser
**
**	params: av -> arguments
**			env -> "environment" struct
**			args -> A pointer to the tree of the arguments in the main()
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- For each argument in av
**		- If the argument is a potential option
**			- Call set_options for catch it and set in env
**		- Or else, the argument is probably a file/dir
**			- Get the informations about the file with lstat and manage the
**			error if it happens. If its the last argument, return FALSE, else
**			continue
**			- Create the node for the file in the tree args
**	- Return TRUE
*/

void			options_parser(char **args, int *options, int *pos_args)
{
	int				i;
	int				takeoptions;

	takeoptions = TRUE;
	i = 0;
	while (args[++i])
	{
		if (((args[i][0] == '-') && (args[i][1] != '\0')) && takeoptions)
		{
			if (args[i][1] == '-')
				takeoptions = FALSE;
			else
				set_options(args[i], options, 1);
		}
		else
		{
			*pos_args = i;
			break;
		}
	}
}

/*******************************************************************************
**							FIN OPTIONS
*******************************************************************************/

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

int		cd_builtin(char **args)
{
	char 	*oldpwd = NULL;
	char 	*pwd = NULL;
	int		pos_args;
	int		options;
	t_varenv *tmp;

	options = 0;
	pos_args = 0;
	options_parser(args, &options, &pos_args);
	if (!(tmp = get_env_var_by_name("PWD")))
	{
		change_env_var(&g_env_lst, "PWD", getcwd(NULL, sizeof(char *)));
		tmp = get_env_var_by_name("PWD");
	}
	oldpwd = tmp->content;
	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
	{
		if (!(tmp = get_env_var_by_name("HOME")))
		{
			ft_printf("minishell: cd: HOME not set");
			return (FALSE);
		}
		pwd = get_final_path(tmp->content);
	}
	else if (ft_strcmp(args[pos_args], "-") == 0)
	{
		if (!(tmp = get_env_var_by_name("OLDPWD")))
		{
			ft_printf("minishell: cd: OLDPWD not set");
			return (FALSE);
		}
		pwd = get_final_path(tmp->content);
	}
	else
		pwd = get_final_path(args[pos_args]);
	if (!pwd || !change_directory(pwd, oldpwd, options))
	{
		ft_strdel(&pwd);
		return (FALSE);
	}
	ft_strdel(&pwd);
	return (TRUE);
}
