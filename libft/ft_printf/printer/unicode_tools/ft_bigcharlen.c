/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigcharlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:06:19 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/31 21:43:23 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_bigcharlen(int i)
{
	if ((MB_CUR_MAX == 1 && i > 255) || (i > 0xD7FF && i < 0xE000))
		return (-1);
	if ((i >= 0 && i <= 0x7f) || MB_CUR_MAX == 1)
		return (1);
	else if (i >= 0x80 && i <= 0x7ff)
		return (2);
	else if (((i >= 0x800 && i <= 0xd7ff)
		|| (i >= 0xe000 && i <= 0xffff)))
		return (3);
	else if (i >= 0x10000 && i <= 0x10ffff)
		return (4);
	else
		return (-1);
}
