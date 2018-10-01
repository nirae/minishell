/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 08:23:34 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/23 22:13:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_base(long long int n, int base)
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

char		*ft_itoa_base(int n, int base)
{
	int		isneg;
	int		len;
	int		i;
	char	*result;

	if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	if ((isneg = !ft_ispositive(n)))
		n = -n;
	len = ft_count_base(n, base);
	if (!(result = ft_strnew(len + isneg + 1)))
		return (0);
	i = 0;
	while (i <= len)
	{
		result[i++] = (n % base) + (n % base > 9 ? 'a' - 10 : 48);
		n = n / base;
	}
	if (isneg)
		result[i] = '-';
	return (ft_strrev(result));
}
