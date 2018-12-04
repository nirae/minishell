/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_complete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:21:23 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/04 18:45:22 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_complete_command(char **str)
{
	char	*line;
	char	*final_str;
	char	*tmp;
	int		i;
	int		escape;

	if (read_prompt(0, &line) < 0)
		return (0);
		// exit(0);
	// a proteger
	final_str = ft_strdup(line);
	ft_strdel(&line);
	i = -1;
	escape =  FALSE;
	while (final_str[++i])
	{
		if (escape)
			escape = FALSE;
		if (final_str[i] == '\\' && final_str[i + 1])
		{
			escape = TRUE;
			i++;
		}
		if ((final_str[i] == ' ' || final_str[i] == '\t') && !escape)
			continue;
		else if (final_str[i] = '$')
		{
			
		}
		else if (final_str[i] == '\"' && !escape)
		{
			while (final_str[i++])
			{
				if (escape)
					escape = FALSE;
				if (final_str[i] == '\\')
				{
					escape = TRUE;
					i++;
				}
				if (final_str[i] == '\"' && !escape)
					break;
				else if (!final_str[i])
				{
					ft_printf("termine ta quote putain>");
					line = NULL;
					if (read_prompt(0, &line) < 0)
						return (0);
						// exit(0);
					tmp = final_str;
					final_str = ft_strjoin(tmp, "\n");
					ft_strdel(&tmp);
					tmp = final_str;
					final_str = ft_strjoin(tmp, line);
					ft_strdel(&line);
					ft_strdel(&tmp);
					continue;
				}
			}
		}
		else if (final_str[i] == '\'' && !escape)
		{
			while (final_str[i++])
			{
				if (escape)
					escape = FALSE;
				if (final_str[i] == '\\')
				{
					escape = TRUE;
					i++;
				}
				if (final_str[i] == '\'' && !escape)
					break;
				else if (!final_str[i])
				{
					ft_printf("termine ta quote putain>");
					line = NULL;
					if (read_prompt(0, &line) < 0)
						return (0);
						// exit(0);
					tmp = final_str;
					final_str = ft_strjoin(tmp, "\n");
					ft_strdel(&tmp);
					tmp = final_str;
					final_str = ft_strjoin(tmp, line);
					ft_strdel(&line);
					ft_strdel(&tmp);
					continue;
				}
			}
		}
	}
	// a proteger
	*str = ft_strdup(final_str);
	return (1);
	// exit(1);
}
