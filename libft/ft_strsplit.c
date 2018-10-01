/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:19:28 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 13:53:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_letters(char *str, char sep)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == sep)
		i++;
	while (str[i] != sep && str[i++] != '\0')
		result++;
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	if (!(tab = ft_memalloc((ft_count_words((char *)s, c) + 1) * sizeof(*tab))))
		return (0);
	i = 0;
	j = 0;
	while (i < ft_count_words((char *)s, c))
	{
		k = 0;
		if (!(tab[i] = ft_strnew(ft_count_letters((char *)&s[j], c) + 1)))
			return (0);
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
			tab[i][k++] = s[j++];
		tab[i++][k] = '\0';
	}
	tab[i] = 0;
	return (tab);
}
