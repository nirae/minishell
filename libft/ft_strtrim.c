/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:51:52 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 13:54:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_set_result(char *r, char const *s, size_t len, size_t s_pos)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		r[i] = s[s_pos];
		s_pos++;
		i++;
	}
	return (r);
}

char		*ft_strtrim(char const *s)
{
	char	*result;
	size_t	i;
	size_t	len;
	size_t	start_position;
	size_t	end_position;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) - 1;
	i = 0;
	while (ft_isspace_tab_nl(s[i]))
		i++;
	start_position = i;
	if (start_position > len)
		return (result = ft_strnew(sizeof(char) * 1));
	i = 0;
	while (ft_isspace_tab_nl(s[len - i]))
		i++;
	end_position = len - i;
	len = (end_position - start_position) + 1;
	if (!(result = ft_strnew(sizeof(char) * len)))
		return (NULL);
	return (ft_set_result(result, s, len, start_position));
}
