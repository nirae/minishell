/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 00:36:16 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 00:55:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_options(char *ops, int *options, int pos)
{
	if (ops[pos] == '\0')
		return (FALSE);
	if (is_valid_option(ops[pos], OPTIONS_ECHO))
		*(options) |= (1 << (ops[pos] - 'a'));
	set_options(ops, options, (pos + 1));
	return (TRUE);
}

int 	echo_builtin(char **args)
{
	int options;
	int z;
	int pos_args;

	pos_args = 0;
	options = 0;
	options_parser(args, &options, &pos_args, set_options);
	z = (pos_args - 1);
	while (args[1 + z])
	{
		ft_printf("%s", args[1 + z]);
		z++;
		if (args[1 + z])
			ft_printf(" ");
	}
	if (!(options & OPT_N))
		ft_printf("\n");
	return (TRUE);
}
