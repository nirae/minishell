/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_sizeflag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:07:59 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:11:40 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		is_valid_sizeflag(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (TRUE);
	return (FALSE);
}
