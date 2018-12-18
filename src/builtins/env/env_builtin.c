/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:09:13 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 22:58:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_error_set_errno(void)
{
	g_my_errno = FAIL_MALLOC;
	return (FALSE);
}

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], OPTIONS_ENV))
		*(options) |= (1 << (ops[pos] - 'a'));
	else
	{
		ft_printf("minishell: env: illegal option -- %c\n"
			, ops[pos]);
		ft_printf("usage: env [-%s] [name=value ..] [utility [argument ...]]\n"
			, OPTIONS_ENV);
		return (FALSE);
	}
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

static void	manage_exec_args(char **args, char **env_tab, int pos_args)
{
	int		i;

	if (args[pos_args])
	{
		exec_command(&args[pos_args], env_tab);
		ft_strtabdel(&env_tab);
	}
	else
	{
		i = -1;
		while (env_tab[++i])
			ft_printf("%s\n", env_tab[i]);
	}
}

int 	env_builtin(char **args)
{
	int		pos_args;
	int		options;
	t_list *env_lst_cpy;
	char	**env_tab;

	options = 0;
	pos_args = 0;
	env_lst_cpy = NULL;
	env_tab = NULL;
	options_parser(args, &options, &pos_args, set_options);
	manage_envvar_args(options, &env_lst_cpy, args, &pos_args);
	if (!pos_args && (options & OPT_I))
		pos_args = 2;
	else if (!pos_args)
		pos_args++;
	if (!env_lst_to_tab(&env_lst_cpy, &env_tab))
		return (malloc_error_set_errno());
	manage_exec_args(args, env_tab, pos_args);
	ft_lstdel(&env_lst_cpy, del_env_var);
	return (TRUE);
}
