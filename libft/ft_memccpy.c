/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:28:41 by ndubouil          #+#    #+#             */
/*   Updated: 2018/07/01 15:07:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*dest;
	char			*source;
	char			stop_char;

	source = (char *)src;
	dest = (char *)dst;
	stop_char = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		if (source[i] == stop_char)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}
