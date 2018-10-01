/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 08:08:30 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/24 08:09:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_lowercase(char *str)
{
	int i;
	int count;

	if (str == NULL)
		return (0);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_islower(str[i]))
			count++;
		i++;
	}
	if (i == count)
		return (1);
	return (0);
}
