/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envvar_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 22:31:59 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 22:42:44 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_equal_sign(char *arg, t_list **result)
{
	t_list		*tmplst;
	char		**tmp;
	int			pos;

	if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
		return (FALSE);
	if (!(tmp = ft_strsplit(arg, '=')))
		return (FALSE);
	pos = ft_strpos(arg, '=');
	if (!(tmplst->content = create_varenv(tmp[0], &arg[pos + 1])))
		return (FALSE);
	if (!(*result))
		*result = tmplst;
	else
		ft_lstadd(result, tmplst);
	ft_strtabdel(&tmp);
	return (TRUE);
}

static t_list	*get_env_var_in_args(char **args, int *pos_args)
{
	int		i;
	t_list	*result;

	result = NULL;
	i = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (!is_equal_sign(args[i], &result))
				return (NULL);
			(*pos_args)++;
		}
		else
			break;
	}
	return (result);
}

int	manage_envvar_args(int options, t_list **env_lst_cpy, char **args,
	int *pos_args)
{
	t_list	*env_var_args;

	env_var_args = NULL;
	if (options & OPT_I)
		*env_lst_cpy = NULL;
	else if (!(ft_lstcpy(g_env_lst, env_lst_cpy)))
		return (FALSE);
	if (!(env_var_args = get_env_var_in_args(&args[*pos_args], pos_args)))
		return (FALSE);
	while (env_var_args)
	{
		if (!change_env_var(env_lst_cpy
				, ((t_varenv*)(env_var_args->content))->name
				, ((t_varenv*)(env_var_args->content))->content))
			return (FALSE);
		env_var_args = env_var_args->next;
	}
	ft_lstdel(&env_var_args, del_env_var);
	return (TRUE);
}
