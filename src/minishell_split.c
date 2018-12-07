/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:19:02 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/07 18:34:48 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(char *str)
{
	int		i;
	int		j;
	int		escape;

	i = -1;
	j = 0;
	escape = FALSE;
	while (str[++i])
	{
		if (escape)
			escape = FALSE;
		if (str[i] == '\\' && str[i + 1])
		{
			escape = TRUE;
			i++;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !escape)
			continue;
		else if (str[i] == '\"' && !escape)
			while (str[i++] && str[i] != '\"');
		else if (str[i] == '\'' && !escape)
			while (str[i++] && str[i] != '\'');
		while (str[i] != ' ' && str[i] != '\t' && str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '\\')
			i++;
		j++;
		if (!str[i])
			break;
	}
	return (j);
}

static int	get_size_of_next_command(char *str)
{
	int i = -1;
	int y = 0;
	int escape = FALSE;

	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			escape = TRUE;
			i++;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !escape)
			continue;
		else if (str[i] == '\"' && !escape)
		{
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\"')
					break;
				y++;
			}
			return (y);
		}
		else if (str[i] == '\'' && !escape)
		{
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\'')
					break;
				y++;
			}
			return (y);
		}
		y = 0;
		while (((str[i] != ' ' && str[i] != '\t' && str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '\\') || escape) && str[i])
		{
			if (escape)
				escape = FALSE;
			y++;
			i++;
		}
		return (y);
	}
	return (y);
}

char		**minishell_split(char *str)
{
	int		i;
	int		j;
	int		y;
	char	**result;
	int		escape;


	if (str == NULL)
		return (NULL);
	if (!(result = ft_memalloc((count_commands(str) + 1) * sizeof(char *) * 10)))
		return (0);
	i = -1;
	j = 0;
	escape = FALSE;
	//ft_printf("nb commands = %d\n", count_commands(str));
	while (str[++i])
	{
		if (escape)
			escape = FALSE;
		// ft_printf("taille: %d\n", get_size_of_next_command(&str[i]));
		if (!(result[j] = ft_strnew((get_size_of_next_command(&str[i]) + 1) * sizeof(char))))
			return (0);
		if (str[i] == '\\')
		{
			escape = TRUE;
			i++;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !escape)
			continue;
		else if (str[i] == '\"' && !escape)
		{
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\"')
					break;
				result[j][y] = str[i];
				y++;
			}
		}
		else if (str[i] == '\'' && !escape)
		{
			y = 0;
			while (str[i++])
			{
				if (str[i] == '\'')
					break;
				result[j][y] = str[i];
				y++;
			}
		}
		y = 0;
		while (((str[i] != ' ' && str[i] != '\t' && str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != '\\') || escape) && str[i])
		{
			if (escape)
				escape = FALSE;
			result[j][y] = str[i];
			y++;
			i++;
		}
		j++;
	}
	return (result);
}
