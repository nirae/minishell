/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 07:49:37 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 12:08:52 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int is_neg;
	int result;

	result = 0;
	i = 0;
	is_neg = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (str[i] - '0') + result * 10;
		i++;
	}
	if (is_neg)
		return (-result);
	return (result);
}
