/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nico <Nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:03:19 by Nico              #+#    #+#             */
/*   Updated: 2018/12/18 21:05:31 by Nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	setenv_builtin(char **args)
{
	int i;

	if (args[1])
		change_env_var(&g_env_lst, args[1], args[2]);
	else
	{
		i = -1;
		while (g_env_tab[++i])
			ft_printf("%s\n", g_env_tab[i]);
	}
	return (TRUE);
}
