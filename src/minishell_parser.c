/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:47:40 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/05 18:52:01 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_varenv		*get_env_var_by_name(char *name)
{
	t_list	*tmp;


	tmp = g_env_lst;
	while(tmp)
	{
		if (ft_strcmp(((t_varenv *)(tmp->content))->name, name) == 0)
			return (((t_varenv *)(tmp->content)));
		tmp = tmp->next;
	}
	return (NULL);
}

int		minishell_parser(char *input, char ****command)
{
	int		i;
	int		y;
	char	**commands;
	t_varenv *myvarenv;

	*command = ft_memalloc((ft_strlen(input) + 1) * 8);

	if (input[0] == 0)
		return (1);
	if (!(commands = ft_strsplit(input, ';')))
		return (FALSE);
	i = -1;
	while (commands[++i])
	{
		if (!((*command)[i] = minishell_split(commands[i])))
			return (FALSE);
		y = -1;
		while ((*command)[i][++y])
		{
			if ((*command)[i][y][0] == '~')
			{
				// a free
				myvarenv = get_env_var_by_name("HOME");
				if (myvarenv != NULL)
				{
					ft_strdel(&(*command)[i][y]);
					// NULL si pas trouve
					if (!((*command)[i][y] = ft_strdup(myvarenv->content)))
						return (0);
				}
			}
		}
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
