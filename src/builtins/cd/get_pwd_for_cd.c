/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd_for_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:33:38 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:37:21 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		home_cd(char **pwd)
{
	char		*str;
	t_varenv	*tmp;

	if (!(tmp = get_env_var_by_name("HOME")))
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (FALSE);
	}
	str = ft_strdup(tmp->content);
	*pwd = get_final_path(&str);
	ft_strdel(&str);
	return (TRUE);
}

static int		oldpwd_cd(char **pwd)
{
	char		*str;
	t_varenv	*tmp;

	if (!(tmp = get_env_var_by_name("OLDPWD")))
	{
		ft_printf("minishell: cd: OLDPWD not set\n");
		return (FALSE);
	}
	str = ft_strdup(tmp->content);
	*pwd = get_final_path(&str);
	ft_strdel(&str);
	return (TRUE);
}

char			*get_pwd_for_cd(int pos_args, char **args)
{
	char		*pwd;
	char		*str;

	if (pos_args == 0 || !args[pos_args] || !args[pos_args][0])
	{
		if (!home_cd(&pwd))
			return (FALSE);
	}
	else if (ft_strcmp(args[pos_args], "-") == 0)
	{
		if (!oldpwd_cd(&pwd))
			return (FALSE);
	}
	else
	{
		str = ft_strdup(args[pos_args]);
		pwd = get_final_path(&str);
		ft_strdel(&str);
	}
	return (pwd);
}
