/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:23:38 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/17 16:31:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Check if the option is valid, return TRUE or FALSE
*/

int		is_valid_option(char c, char *options)
{
	if (!ft_isprint(c) || (!ft_strchr(options, c) && c != ' ') || !c)
		return (FALSE);
	return (TRUE);
}

/*
**	The parser
**
**	params: av -> arguments
**			env -> "environment" struct
**			args -> A pointer to the tree of the arguments in the main()
**	return: FALSE if failed or TRUE
**
**	Description:
**
**	- For each argument in av
**		- If the argument is a potential option
**			- Call set_options for catch it and set in env
**		- Or else, the argument is probably a file/dir
**			- Get the informations about the file with lstat and manage the
**			error if it happens. If its the last argument, return FALSE, else
**			continue
**			- Create the node for the file in the tree args
**	- Return TRUE
*/

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
			break;
		}
	}
}
