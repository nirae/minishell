/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulli_itoa_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 20:14:51 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/23 22:14:28 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_base(unsigned long long int n, int base)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char		*ft_ulli_itoa_base(unsigned long long int n, char *base_str)
{
	int		len;
	int		base;
	char	*result;

	base = ft_strlen(base_str);
	len = ft_count_base(n, base);
	if (!(result = ft_strnew(len + 1)))
		return (NULL);
	result[0] = '0';
	while (n != 0)
	{
		result[--len] = base_str[n % base];
		n = n / base;
	}
	return (result);
}
