/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nico <Nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 19:00:40 by Nico              #+#    #+#             */
/*   Updated: 2018/12/20 00:35:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_letters(char *str)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == ' ' && str[i] == '\t' && str[i] == '\n' && str[i])
		i++;
	while (str[i] != ' ' && str[i] != '$' && str[i++])
		result++;
	return (result);
}

static char		*one_more_split(char *s)
{
	char	*result;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (!(result = ft_strnew(count_letters(s) + 1)))
		return (NULL);
	if (s[i] == ' ' || !s[i] || s[i] == '\n'|| s[i] == '\t')
		return (NULL);
	while (s[i] != ' ' && s[i] != ';' && (s[i] != '$' || s[i - 1] == '$')
		&& s[i])
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
}

static char		*get_beg_of_str(char *str, int i)
{
	str[i] = '\0';
	return (ft_strdup(str));
}

int			replace_dollar(char **final_str, int *i)
{
	char *var;
	char *beg;
	char *end;
	char *tmp;
	char *result;

	result = *final_str;
	if (!(var = one_more_split(&result[*i + 1])))
		return (FALSE);
	beg = get_beg_of_str(result, *i);
	if (get_env_var_by_name(var))
	{
		tmp = beg;
		beg = ft_strjoin(tmp, get_env_var_by_name(var)->content);
		ft_strdel(&tmp);
	}
	end = ft_strdup(&result[*i + ft_strlen(var) + 1]);
	result = ft_strjoin(beg, end);
	*i = ft_strlen(beg) - 1;
	ft_strdel(&var);
	ft_strdel(&beg);
	ft_strdel(&end);
	if (result)
	{
		ft_strdel(final_str);
		*final_str = result;
	}
	return (TRUE);
}
