/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nico <Nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:10:34 by Nico              #+#    #+#             */
/*   Updated: 2018/12/18 18:16:25 by Nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_ok(char c)
{
	if (c != ' ' && c != '\t' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

static int			count_words(char *str)
{
	if (*str == '\0')
		return (0);
	else if (ft_is_ok(*str) && !ft_is_ok(*(str + 1)))
		return (1 + count_words(str + 1));
	return (0 + count_words(str + 1));
}

static int	count_letters(char *str)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
		&& str[i++] != '\0')
		result++;
	return (result);
}

char		**ft_strsplit_whitespace(char const *s)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	if (!(tab = ft_memalloc((count_words((char *)s) + 1) * sizeof(*tab))))
		return (0);
	i = 0;
	j = 0;
	while (i < count_words((char *)s))
	{
		k = 0;
		if (!(tab[i] = ft_strnew(count_letters((char *)&s[j]) + 1)))
			return (0);
		while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
			j++;
		while (s[j] != ' ' && s[j] != '\t' && s[j] != '\n' && s[j] != '\0')
			tab[i][k++] = s[j++];
		tab[i++][k] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
