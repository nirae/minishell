/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_big_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:06:45 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/28 15:29:17 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Printer for flag 'C'
*/

int		print_big_char(t_env *env)
{
	long long int		i;
	char				result[5];
	int					len;

	i = -1;
	env->types.i = va_arg(env->va, int);
	if ((len = get_big_char(env, env->types.i, result)) == -1)
	{
		env->len = -1;
		return (FALSE);
	}
	env->len += (env->types.i == 0) ? 1 : 0;
	if (env->flags.width > 1)
	{
		if (env->flags.align == RIGHT)
			while (++i < env->flags.width - len)
				env->len += putchar_in_buffer(&env->buff, ' ');
		env->len += putstr_in_buffer(&env->buff, result);
		if (env->flags.align == LEFT)
			while (++i < env->flags.width - len)
				env->len += putchar_in_buffer(&env->buff, ' ');
		return (TRUE);
	}
	env->len += putstr_in_buffer(&env->buff, result);
	return (TRUE);
}
