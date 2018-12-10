/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:10:36 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/10 19:43:29 by ndubouil         ###   ########.fr       */
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

int		ft_count_words_escape(char *str, char sep)
{
	int 	i = -1;
	int 	j = 1;
	int		escape = FALSE;
	int		nb_quote = 0;
	int		quote = 0;

	while (str[++i])
	{
		// ft_printf("i = %c, escape = %d, nb_quote = %d, quote = %d, mots = %d\n", str[i], escape, nb_quote, quote, j);
		if (str[i] == '\"' && !escape)
		{
			// Si une double quote est deja ouverte
			if (quote == DOUBLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = DOUBLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == '\'' && !escape)
		{
			// Si une simple quote est deja ouverte
			if (quote == SIMPLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = SIMPLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == sep && !escape && (nb_quote % 2) == 0)
		{
			// Nouveau mot
			if (str[i + 1])
				j++;
			continue;
		}
		else if (str[i] == '\\' && (nb_quote % 2) == 0)
		{
			if (escape)
				escape = FALSE;
			else
			{
				escape = TRUE;
				continue;
			}
		}
		if (escape)
			escape = FALSE;
	}
	return (j);
}

int 	ft_count_letters_escape(char *str, char sep)
{
	int 	i = -1;
	// int 	j = 1;
	int		escape = FALSE;
	int		nb_quote = 0;
	int		quote = 0;
	// int		skip = 0;
	//
	// while (str[i + 1] == sep)
	// {
	// 	i++;
	// 	skip++;
	// }
	while (str[i + 1] == sep)
		i++;
	while (str[++i])
	{
		// ft_printf("i = %c, escape = %d, nb_quote = %d, quote = %d\n", str[i], escape, nb_quote, quote);
		if (str[i] == '\"' && !escape)
		{
			// Si une double quote est deja ouverte
			if (quote == DOUBLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = DOUBLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == '\'' && !escape)
		{
			// Si une simple quote est deja ouverte
			if (quote == SIMPLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = SIMPLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == sep && !escape && (nb_quote % 2) == 0)
		{
			return (i);
			// Nouveau mot
			// if (str[i + 1])
				// j++;
			// continue;
		}
		else if (str[i] == '\\' && (nb_quote % 2) == 0)
		{
			if (escape)
				escape = FALSE;
			else
			{
				escape = TRUE;
				continue;
			}
		}
		if (escape)
			escape = FALSE;
	}
	return (i);
}

char		**ft_strsplit_with_escape(char *str, char sep)
{
	int 	i = -1;
	int 	j;
	int		z;
	int		escape = FALSE;
	int		nb_quote = 0;
	int		quote = 0;
	char	**tab;
	int		nb_words;

	int pos = 0;

	if (str == NULL)
		return (NULL);
	nb_words = ft_count_words_escape(str, sep);
	if (!(tab = ft_memalloc((nb_words + 1) * sizeof(*tab))))
		return (0);
	j = -1;
	while (++j < nb_words)
	{
		// ft_printf("pos avant = %d\n", pos);
		int nb_letters = ft_count_letters_escape(&str[pos], sep);
		// ft_printf("nb letters = %d\n", nb_letters);
		tab[j] = ft_strnew(nb_letters + 1);
		// tab[j] = ft_strnew(1000);
		pos += nb_letters;
		// ft_printf("pos apres = %d\n", pos);
	}
	j = 0;
	z = 0;
	while (str[++i])
	{
		// ft_printf("ou j'en suis au debut : %c\n", str[i]);
		// ft_printf("i = %c, escape = %d, nb_quote = %d, quote = %d, mots = %d\n", str[i], escape, nb_quote, quote, j);
		if (str[i] == '\"' && !escape && quote != SIMPLE_QUOTE)
		{
			tab[j][z++] = str[i];
			// Si une double quote est deja ouverte
			if (quote == DOUBLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = DOUBLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == '\'' && !escape && quote != DOUBLE_QUOTE)
		{
			tab[j][z++] = str[i];
			// Si une simple quote est deja ouverte
			if (quote == SIMPLE_QUOTE && (nb_quote % 2) != 0)
			{
				quote = 0;
				nb_quote++;
				continue;
			}
			// Si il y a pas de quotes d'ouverte
			else if (!quote)
			{
				quote = SIMPLE_QUOTE;
				nb_quote++;
				continue;
			}
		}
		else if (str[i] == sep && !escape && (nb_quote % 2) == 0)
		{
			// Nouveau mot
			if (str[i + 1])
			{
				z = 0;
				// ft_printf("avant de changer de mot = %s\n", tab[j]);
				j++;
			}
			continue;
		}
		else if (str[i] == '\\' && (nb_quote % 2) == 0)
		{
			// ft_printf("ICI\n");
			if (escape)
				escape = FALSE;
			else
			{
				escape = TRUE;
				continue;
			}
		}
		if (escape)
			escape = FALSE;
		// ft_printf("mise dans le tab de : %c, z = %d\n", str[i], z);
		tab[j][z++] = str[i];
	}
	tab[j + 1] = NULL;
//DEBUG
	j = -1;
	while (tab[++j])
		ft_printf("split escape [%d] = %s\n", j, tab[j]);
// FIN DEBUG
	return (tab);
}

// int	ft_count_words_escape(char *str, char sep)
// {
// 	int		i;
// 	int		j;
// 	int		escape;
//
// 	i = 0;
// 	j = 0;
// 	escape = FALSE;
// 	while (str[i])
// 	{
// 		if (escape)
// 			escape = FALSE;
// 		if (str[i] == '\\' && str[i + 1])
// 		{
// 			escape = TRUE;
// 			i++;
// 			if (str[i] == '\\' && str[i + 1])
// 			{
// 				escape = FALSE;
// 				i++;
// 			}
// 		}
// 		while (str[i] == sep && !escape)
// 		{
// 			i++;
// 			if (str[i] == '\\' && str[i + 1])
// 			{
// 				escape = TRUE;
// 				i++;
// 			}
// 		}
// 		while ((str[i] != sep || escape) && str[i] && str[i] != '\\')
// 		{
// 			i++;
// 			if (escape)
// 				escape = FALSE;
// 		}
// 		if ((str[i] == sep && !escape) || !str[i])
// 		{
// 			j++;
// 			if (str[i] == sep && !escape)
// 				i++;
// 		}
// 	}
// 	return (j);
// }

// static int	ft_count_letters(char *str, char sep)
// {
// 	int i;
// 	int result;
// 	int escape;
//
// 	i = 0;
// 	result = 0;
// 	escape = FALSE;
// 	if (str[i] == '\\')
// 	{
// 		escape = TRUE;
// 		i++;
// 	}
// 	while (str[i] == sep && !escape)
// 		i++;
// 	while (str[i])
// 	{
// 		if (escape)
// 			escape = FALSE;
// 		if (str[i] == '\\')
// 		{
// 			escape = TRUE;
// 			i++;
// 		}
// 		if (str[i] == sep && !escape)
// 			break;
// 		result++;
// 		i++;
// 	}
// 	return (result);
// }
//
// char		**ft_split_escape(char *str, char sep)
// {
// 	char	**tab;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		escape;
//
// 	if (str == NULL)
// 		return (NULL);
// 	ft_printf("nb = %d\n", ft_count_words_escape((char *)str, sep));
// 	if (!(tab = ft_memalloc((ft_count_words_escape((char *)str, sep) + 1) * sizeof(*tab))))
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	escape = FALSE;
// 	while (i < ft_count_words_escape((char *)str, sep))
// 	{
// 		k = 0;
// 		ft_printf("nb letters = %d\n", ft_count_letters((char *)&str[j], sep));
// 		if (!(tab[i] = ft_strnew(ft_count_letters((char *)&str[j], sep) + 1)))
// 			return (0);
// 		if (str[j] == '\\')
// 		{
// 			escape = TRUE;
// 			j++;
// 		}
// 		while (str[j] == sep && !escape)
// 			j++;
// 		while ((str[j] != sep || escape) && str[j])
// 		{
// 			tab[i][k++] = str[j++];
// 			if (str[j] == '\\')
// 			{
// 				escape = TRUE;
// 				j++;
// 			}
// 			else if (str[j] == sep)
// 				escape = FALSE;
// 		}
// 		tab[i++][k] = '\0';
// 	}
// 	tab[i] = 0;
// 	return (tab);
// }
