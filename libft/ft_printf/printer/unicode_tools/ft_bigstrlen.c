/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:27:54 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 19:28:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_bigstrlen(wchar_t *str)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i] != 0)
		len += ft_bigcharlen(str[i]);
	return (len);
}
