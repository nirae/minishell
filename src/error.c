/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:19:30 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 22:44:57 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*perm_denied(char *str)
{
	ft_printf("minishell: %s: Permission denied\n", str);
	return (NULL);
}

void	*cmd_not_found(char *str)
{
	ft_printf("minishell: command not found: %s\n", str);
	return (NULL);
}

void	error(void)
{
	ft_printf("minishell: critical fail\n");
	exit_builtin("1", NULL);
}
