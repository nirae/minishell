/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:37:05 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/16 19:37:27 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path_errors(char *path)
{
	struct stat st;

	if ((stat(path, &st)) < 0)
	{
		ft_printf("minishell: cd: no such file or directory: %s\n", path);
		return (FALSE);
	}
	else
	{
		if (!S_ISDIR(st.st_mode))
		{
			ft_printf("minishell: cd: not a directory: %s\n", path);
			return (FALSE);
		}
	}
	return (TRUE);
}
