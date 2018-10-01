/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 08:35:43 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 14:39:09 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (source < dest)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			dest[i] = source[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dst);
}
