/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:10:36 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/04 14:11:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_is_ok(char b, char c, char sep)
// {
// 	if (c != sep && c != '\0' && b != '\\')
// 		return (1);
// 	return (0);
// }

// static int			ft_count_words_escape(char *str, char sep)
// {
// 	if (*str == '\0')
// 		return (0);
// 	else if (ft_is_ok(*str, *str, sep) && !ft_is_ok(*str, *(str + 1), sep))
// 		return (1 + ft_count_words(str + 1, sep));
// 	return (0 + ft_count_words(str + 1, sep));
// }

static int	ft_count_words_escape(char *str, char sep)
{
	int		i;
	int		j;
	int		escape;

	i = 0;
	j = 0;
	escape = FALSE;
	while (str[i])
	{
		if (escape)
			escape = FALSE;
		if (str[i] == '\\' && str[i + 1])
		{
			escape = TRUE;
			i++;
			if (str[i] == '\\' && str[i + 1])
			{
				escape = FALSE;
				i++;
			}
		}
		while (str[i] == sep && !escape)
		{
			i++;
			if (str[i] == '\\' && str[i + 1])
			{
				escape = TRUE;
				i++;
			}
		}
		while ((str[i] != sep || escape) && str[i] && str[i] != '\\')
		{
			i++;
			if (escape)
				escape = FALSE;
		}
		if ((str[i] == sep && !escape) || !str[i])
		{
			j++;
			if (str[i] == sep && !escape)
				i++;
		}
	}
	return (j);
}

static int	ft_count_letters(char *str, char sep)
{
	int i;
	int result;
	int escape;

	i = 0;
	result = 0;
	escape = FALSE;
	if (str[i] == '\\')
	{
		escape = TRUE;
		i++;
	}
	while (str[i] == sep && !escape)
		i++;
	while (str[i])
	{
		if (escape)
			escape = FALSE;
		if (str[i] == '\\')
		{
			escape = TRUE;
			i++;
		}
		if (str[i] == sep && !escape)
			break;
		result++;
		i++;
	}
	return (result);
}

char		**ft_split_escape(char *str, char sep)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		escape;

	if (str == NULL)
		return (NULL);
	ft_printf("nb = %d\n", ft_count_words_escape((char *)str, sep));
	if (!(tab = ft_memalloc((ft_count_words_escape((char *)str, sep) + 1) * sizeof(*tab))))
		return (0);
	i = 0;
	j = 0;
	escape = FALSE;
	while (i < ft_count_words_escape((char *)str, sep))
	{
		k = 0;
		ft_printf("nb letters = %d\n", ft_count_letters((char *)&str[j], sep));
		if (!(tab[i] = ft_strnew(ft_count_letters((char *)&str[j], sep) + 1)))
			return (0);
		if (str[j] == '\\')
		{
			escape = TRUE;
			j++;
		}
		while (str[j] == sep && !escape)
			j++;
		while ((str[j] != sep || escape) && str[j])
		{
			tab[i][k++] = str[j++];
			if (str[j] == '\\')
			{
				escape = TRUE;
				j++;
			}
			else if (str[j] == sep)
				escape = FALSE;
		}
		tab[i++][k] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
