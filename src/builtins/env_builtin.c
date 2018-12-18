/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:09:13 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 04:38:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void		print_lstenv(t_list *lst)
// {
// 	ft_printf("%s=%s\n", ((t_varenv *)(lst->content))->name, ((t_varenv *)(lst->content))->content);
// }

/*
**	Options setter
*/

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

t_list		*ft_lstcpy(t_list *src, t_list **dest)
{
	t_list		*tmp;
	t_list		*tmplst;
	char *name;
	char *content;

	(*dest) = NULL;
	tmp = src;
	while (tmp)
	{
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			ft_printf("lstnew a foire\n");
		name = ft_strdup(((t_varenv*)(tmp->content))->name);
		content = ft_strdup(((t_varenv*)(tmp->content))->content);
		tmplst->content = create_varenv(name, content);
		if (!(*dest))
			(*dest) = tmplst;
		else
			ft_lstaddend(dest, tmplst);
		tmp = tmp->next;
		ft_strdel(&name);
		ft_strdel(&content);
	}
	return (*dest);
}

static t_list	*get_env_var_for_envbt(char **args, int *pos_args)
{
	int		i;
	t_list	*result;
	t_list	*tmplst;
	char	**tmp;
	int 	pos;

	result = NULL;
	i = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
				ft_printf("lstnew a foire\n");
			if (!(tmp = ft_strsplit(args[i], '=')))
				ft_printf("strsplit a foire\n");
			pos = ft_strpos(args[i], '=');
			tmplst->content = create_varenv(tmp[0], &args[i][pos + 1]);
			if (!(result))
				result = tmplst;
			else
				ft_lstadd(&result, tmplst);
			ft_strtabdel(&tmp);
			tmp = ft_strsplit(args[i], '=');
			(*pos_args)++;
		}
		else
			break;
	}
	return (result);
}

int 	env_builtin(char **args)
{
	int		pos_args;
	int		options;
	t_list *env_lst_cpy;
	t_list *env_var_args;
	char	**env_tab;
	int i;

	(void)args;
	options = 0;
	pos_args = 0;
	env_lst_cpy = NULL;
	env_var_args = NULL;
	env_tab = NULL;
	options_parser(args, &options, &pos_args, set_options);
	if (options & OPT_I)
		env_lst_cpy = NULL;
	else if (!(ft_lstcpy(g_env_lst, &env_lst_cpy)))
		ft_printf("fail cpy\n");
	env_var_args = get_env_var_for_envbt(&args[pos_args], &pos_args);
	while (env_var_args)
	{
		change_env_var(&env_lst_cpy, ((t_varenv*)(env_var_args->content))->name, ((t_varenv*)(env_var_args->content))->content);
		env_var_args = env_var_args->next;
	}
	if (pos_args == 0)
		pos_args++;
	env_lst_to_tab(&env_lst_cpy, &env_tab);
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
		// ft_lstiter(env_lst_cpy, print_lstenv);
	ft_lstdel(&env_lst_cpy, del_env_var);
	ft_lstdel(&env_var_args, del_env_var);
	return (TRUE);
}
