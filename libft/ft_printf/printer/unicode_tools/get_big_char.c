/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_big_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:57:16 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 19:10:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		second_case(int c, char result[5])
{
	result[0] = 0xc0 | ((c >> 6) & 0x1f);
	if (MB_CUR_MAX != 1)
	{
		result[1] = 0x80 | (c & 0x3f);
		result[2] = '\0';
	}
	else
		result[1] = '\0';
}

void		third_case(int c, char result[5])
{
	result[0] = 0xe0 | ((c >> 12) & 0x0f);
	if (MB_CUR_MAX != 1)
	{
		result[1] = 0x80 | ((c >> 6) & 0x3f);
		result[2] = 0x80 | (c & 0x3f);
		result[3] = '\0';
	}
	else
		result[1] = '\0';
}

void		fourth_case(int c, char result[5])
{
	result[0] = 0xf0 | ((c >> 18) & 0x07);
	if (MB_CUR_MAX != 1)
	{
		result[1] = 0x80 | ((c >> 12) & 0x3f);
		result[2] = 0x80 | ((c >> 6) & 0x3f);
		result[3] = 0x80 | (c & 0x3f);
		result[4] = '\0';
	}
	else
		result[1] = '\0';
}

void		dispatch_size(t_env *env, int c, int len, char result[5])
{
	if (len == 1)
	{
		result[0] = (unsigned char)c;
		result[1] = '\0';
	}
	else if (len == 2)
		second_case(c, result);
	else if (len == 3)
		third_case(c, result);
	else if (len == 4)
		fourth_case(c, result);
	else
		env->len = -1;
}

/*
**	Get a unicode char
** 	Return the len of the "big char"
**	Put the "big char" in the param "result"
**	Take the env structure for manage the error
*/

int			get_big_char(t_env *env, int c, char result[5])
{
	int		len;

	if ((len = ft_bigcharlen(c)) == -1)
		return (-1);
	dispatch_size(env, c, len, result);
	return (len);
}
