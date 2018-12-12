/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:10:36 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/12 15:42:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
