/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_complete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:21:23 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/01 04:09:07 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_complete_command(char **str)
{
	char	*line;
	char	*final_str;
	int		i;

	if (read_prompt(0, &line) <= 0)
		return (0);
	if (!(final_str = ft_strdup(line)))
		return (FALSE);
	ft_strdel(&line);
	i = -1;
	while (final_str[++i])
		if (final_str[i] == '$' && final_str[i + 1] && final_str[i + 1] != '$')
			replace_dollar(&final_str, &i);
	*str = final_str;
	return (1);
}
