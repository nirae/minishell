/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 10:51:16 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:54:14 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Printer for flag 'c'
*/

int		print_char(t_env *env)
{
	long long int		i;

	i = -1;
	env->types.c = (char)va_arg(env->va, int);
	if (env->flags.width < 0)
	{
		env->flags.align = LEFT;
		env->flags.width = -env->flags.width;
	}
	if (env->flags.width > 1)
	{
		if (env->flags.align == RIGHT)
			while (++i < env->flags.width - 1)
				env->len += putchar_in_buffer(&env->buff, ' ');
		env->len += putchar_in_buffer(&env->buff, env->types.c);
		if (env->flags.align == LEFT)
			while (++i < env->flags.width - 1)
				env->len += putchar_in_buffer(&env->buff, ' ');
		return (TRUE);
	}
	env->len += putchar_in_buffer(&env->buff, env->types.c);
	return (TRUE);
}
