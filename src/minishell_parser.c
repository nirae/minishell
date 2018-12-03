/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:47:40 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/03 19:56:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_parser(char *input, char ****command)
{
	int		i;
	char	**commands;

	*command = ft_memalloc((ft_strlen(input) + 1) * 8);

	if (input[0] == 0)
		return (1);
	if (!(commands = ft_split_escape(input, ';')))
		return (FALSE);
	//ft_split_escape(input, ';');
	i = -1;
	while (commands[++i])
	{
		ft_printf("debug: %s\n", commands[i]);
		if (!((*command)[i] = minishell_split(commands[i])))
			return (FALSE);
	}
	(*command)[i] = NULL;

	// DEBUG //
	// i = -1;
	// int y;
	// ft_printf("DEBUG:\n");
	// while (commands[++i])
	// {
	// 	y = -1;
	// 	while ((*command)[i][++y])
	// 	{
	// 		ft_printf("commande %d = %s\n", y, (*command)[i][y]);
	// 	}
	// }
	// FIN DEBUG //
	return (1);
}
