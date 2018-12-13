/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:26:03 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/13 22:42:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (name[0] == '/')
		return (name);
	if (name[0] == '.' && name[1] == '/')
	{
		tmp = ft_strdup(&name[2]);
		ft_strdel(&name);
		name = tmp;
	}
	if (parent == NULL)
	{
		if (!(result = ft_strjoin("./", name)))
			return (NULL);
		return (result);
	}
	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			return (NULL);
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			return (NULL);
	}
	if (!(result = ft_strjoin(tmp, name)))
		return (NULL);
	ft_strdel(&tmp);
	return (result);
}

int				options_parser(char **args, int *options, int *pos_args)
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
	return (TRUE);
}

int		cd_builtin(char **args)
{
	char 	oldpwd[PATH_MAX + 1];
	char 	pwd[PATH_MAX + 1];
	int		pos_args;
	int		options;
	t_varenv	*tmp;

	options = 0;
	pos_args = 0;
	options_parser(args, &options, &pos_args);
	ft_printf("options = %d, pos_args = %d, argument courant = %s\n", options, pos_args, args[pos_args]);
	// recupere le pwd
	getcwd(oldpwd, PATH_MAX + 1);
	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
	{
		ft_printf("complete path = %s\n", get_complete_path(get_env_var_by_name("PWD")->content, get_env_var_by_name("HOME")->content));
		tmp = get_env_var_by_name("HOME");
		if ((chdir(tmp->content)) < 0)
			ft_printf("chdir failed, errno = %d\n", errno);
		else
		{
			if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
				ft_printf("OLDPWD not found\n");
			// PWD
			// recupere le pwd
			getcwd(pwd, PATH_MAX + 1);
			if (!(change_env_var(&g_env_lst, "PWD", pwd)))
				ft_printf("PWD not found\n");
			ft_printf("... moving to %s ....\n", tmp->content);
		}
	}
	else if (ft_strcmp(args[pos_args], "-") == 0)
	{
		if ((chdir(get_env_var_by_name("OLDPWD")->content)) < 0)
			ft_printf("chdir failed\n");
		else
		{
			if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
				ft_printf("OLDPWD not found\n");
			// PWD
			// recupere le pwd
			getcwd(pwd, PATH_MAX + 1);
			if (!(change_env_var(&g_env_lst, "PWD", pwd)))
				ft_printf("PWD not found\n");
			ft_printf("... moving to %s ....\n", get_env_var_by_name("OLDPWD")->content);
		}
	}
	else
	{
		if ((chdir(args[pos_args])) < 0)
			ft_printf("chdir failed\n");
		else
		{
			ft_printf("complete path = %s\n", get_complete_path(get_env_var_by_name("PWD")->content, args[pos_args]));
			if (!(change_env_var(&g_env_lst, "OLDPWD", oldpwd)))
				ft_printf("OLDPWD not found\n");
			// PWD
			// recupere le pwd
			getcwd(pwd, PATH_MAX + 1);
			if (!(change_env_var(&g_env_lst, "PWD", pwd)))
				ft_printf("PWD not found\n");
			ft_printf("... moving to %s ....\n", args[pos_args]);
		}
	}
	return (TRUE);
}
