/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:07:14 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 04:22:35 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_builtin(char **args)
{
	if (args[1])
		remove_env_var(&g_env_lst, args[1]);
	else
		return (FALSE);
	return (TRUE);
}
