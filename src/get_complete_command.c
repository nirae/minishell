/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_complete_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:21:23 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/12 16:24:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_letterssss(char *str)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i] != ' ' && str[i] != '$' && str[i++])
		result++;
	return (result);
}

char		*one_more_split(char *s)
{
	char	*result;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (!(result = ft_strnew(ft_count_letterssss(s) + 1)))
		return (NULL);
	if (s[i] == ' ' || !s[i] || s[i] == '\n'|| s[i] == '\t')
		return (NULL);
	while (s[i] != ' ' && s[i] != '\"' && s[i] != '\'' && s[i] != ';' &&
		(s[i] != '$' || s[i - 1] == '$') && s[i])
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
}

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
		else if (final_str[i] == '$')
		{
			char *var;
			char *debut;
			char *fin;
			char *tmp;
			t_varenv *myenvvar;

			// a proteger
			if (!(var = one_more_split(&final_str[i + 1])))
				continue;
			final_str[i] = '\0';
			debut = ft_strdup(final_str);
			final_str[i] = '$';
			tmp = debut;
			if (!(myenvvar = get_env_var_by_name(var)))
				debut = ft_strdup(tmp);
			else
				debut = ft_strjoin(tmp, myenvvar->content);
			// Si NULL = pas trouve
			// if (!(debut = ft_strjoin(tmp, myenvvar->content)))
			// 	debut = ft_strdup(tmp);
			ft_strdel(&tmp);
			// a proteger
			fin = ft_strdup(&final_str[i + ft_strlen(var) + 1]);
			// a proteger
			final_str = ft_strjoin(debut, fin);
			i = ft_strlen(debut) - 1;
			ft_strdel(&debut);
			ft_strdel(&fin);
			continue;
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
					// a proteger
					final_str = ft_strjoin(tmp, "\n");
					ft_strdel(&tmp);
					tmp = final_str;
					// a proteger
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
