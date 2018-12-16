/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:47:40 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/15 23:37:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	replace_tild(char **str)
{
	t_varenv	*myvarenv;

	myvarenv = get_env_var_by_name("HOME");
	if (myvarenv && myvarenv->content)
	{
		ft_strdel(str);
		if (!(*str = ft_strdup(myvarenv->content)))
			return (FAIL_MALLOC);
		return (TRUE);
	}
	return (FALSE);
}

static	int split_each_commands(char **commands, char ****commands_tab)
{
	int			i;
	int			y;

	i = -1;
	while (commands[++i])
	{
		if (!((*commands_tab)[i] = minishell_split(commands[i])))
			return (FAIL_);
		y = -1;
		while ((*commands_tab)[i][++y])
		{
			if ((*commands_tab)[i][y][0] == '~')
				if (!(replace_tild(&(*commands_tab)[i][y])))
					return (FAIL_);
		}
	}
	(*commands_tab)[i] = NULL;
	return (TRUE);
}

// static	void free_separated_commands(char ***tab)
// {
// 	int		i;
//
// 	i = -1;
// 	while ((*tab)[++i])
// 		ft_strdel(&(*tab)[i]);
// }

int		minishell_parser(char *input, char ****commands_tab)
{
	char	**separated_commands;

	*commands_tab = ft_memalloc((ft_strlen(input) + 1) * sizeof(char *));
	if (!input[0])
		return (TRUE);
	// ft_printf("count words escape = %d\n", ft_count_words_escape(input, ';'));
	if (!(separated_commands = ft_strsplit_with_escape(input, ';')))
		return (FAIL_);
	if (!(split_each_commands(separated_commands, commands_tab)))
		return (FAIL_);

	/*
	** DEBUG
	*/
	// int i = -1;
	// int y;
	// ft_printf("DEBUG:\n");
	// while (separated_commands[++i])
	// {
	// 	y = -1;
	// 	while ((*commands_tab)[i][++y])
	// 	{
	// 		ft_printf("commande %d, arg %d = %s\n", i, y, (*commands_tab)[i][y]);
	// 	}
	// }
	/*
	** FIN DEBUG
	*/
	ft_strtabdel(&separated_commands);
	// free_separated_commands(&separated_commands);
	return (TRUE);
}
