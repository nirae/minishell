/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:22:31 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/23 08:42:46 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*result;
	size_t	i;

	result = (void *)malloc(size);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		i++;
	}
	return ((void *)result);
}
