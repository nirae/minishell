/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:47:40 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/19 16:48:27 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_tild(char **str)
{
	t_varenv	*myvarenv;
	char		*tmp;

	myvarenv = get_env_var_by_name("HOME");
	if (myvarenv && myvarenv->content)
	{
		if ((*str)[1] == '/')
			tmp = ft_strdup(&(*str)[1]);
		else
			tmp = ft_strdup("");
		ft_strdel(str);
		if (!(*str = ft_strjoin(myvarenv->content, tmp)))
		{
			ft_strdel(&tmp);
			return (FALSE);
		}
		ft_strdel(&tmp);
		return (TRUE);
	}
	return (FALSE);
}

static int	split_each_commands(char **commands, char ****commands_tab)
{
	int			i;
	int			y;

	i = -1;
	while (commands[++i])
	{
		if (!((*commands_tab)[i] = ft_strsplit_whitespace(commands[i])))
			return (FALSE);
		y = -1;
		while ((*commands_tab)[i][++y])
		{
			if ((*commands_tab)[i][y][0] == '~')
				replace_tild(&(*commands_tab)[i][y]);
		}
	}
	(*commands_tab)[i] = NULL;
	return (TRUE);
}

int			minishell_parser(char *input, char ****commands_tab)
{
	char	**separated_commands;

	if (!input[0])
		return (FALSE);
	if (!(*commands_tab = ft_memalloc((ft_strlen(input) + 1) * sizeof(char *))))
		return (FALSE);
	if (!(separated_commands = ft_strsplit(input, ';')))
		return (FALSE);
	if (!(split_each_commands(separated_commands, commands_tab)))
		return (FALSE);
	ft_strtabdel(&separated_commands);
	return (TRUE);
}
