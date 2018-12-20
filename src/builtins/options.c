/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:23:38 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:43:35 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_option(char c, char *options)
{
	if (!ft_isprint(c) || (!ft_strchr(options, c) && c != ' ') || !c)
		return (FALSE);
	return (TRUE);
}

void	options_parser(char **args, int *options, int *pos_args,
			int (*set_options)(char *, int *, int))
{
	int				i;
	int				takeoptions;

	takeoptions = TRUE;
	i = 0;
	while (args[++i])
	{
		if (((args[i][0] == '-') && (args[i][1] != '\0')) && takeoptions)
		{
			if (args[i][1] == '-')
				takeoptions = FALSE;
			else
				set_options(args[i], options, 1);
		}
		else
		{
			*pos_args = i;
			break ;
		}
	}
}
