/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 08:25:04 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 08:36:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_ok(char c, char sep)
{
	if (c != sep && c != '\0')
		return (1);
	return (0);
}

int			ft_count_words(char *str, char sep)
{
	if (*str == '\0')
		return (0);
	else if (ft_is_ok(*str, sep) && !ft_is_ok(*(str + 1), sep))
		return (1 + ft_count_words(str + 1, sep));
	return (0 + ft_count_words(str + 1, sep));
}
