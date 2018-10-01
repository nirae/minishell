/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 23:28:07 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/28 10:39:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		dispatch(t_env *env)
{
	if ((env->flags.type == 'c' && env->flags.size == L) ||
			env->flags.type == 'C')
		return (print_big_char(env));
	else if ((env->flags.type == 's' && env->flags.size == L) ||
			env->flags.type == 'S')
		return (print_big_string(env));
	else if (env->flags.type == '%')
		return (print_percent(env));
	else if (env->flags.type == 'c')
		return (print_char(env));
	else if (env->flags.type == 's')
		return (print_string(env));
	else if (env->flags.type == 'p')
		return (print_address(env));
	else if (env->flags.type == 'd' || env->flags.type == 'i' ||
			env->flags.type == 'D')
		return (print_number(env));
	else if (env->flags.type == 'u' || env->flags.type == 'U')
		return (print_unsigned_number(env));
	else if (env->flags.type == 'o' || env->flags.type == 'O')
		return (print_octal(env));
	else if (env->flags.type == 'x' || env->flags.type == 'X')
		return (print_hexa(env));
	else
		return (FALSE);
}

int				printer(t_env *env)
{
	int		ret;

	ret = dispatch(env);
	if (ret == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (env->len == -1)
	{
		delete_end_of_buffer(&env->buff, env->buff.pos_last_conv);
		print_buffer(&env->buff);
		return (FAIL);
	}
	env->buff.pos_last_conv = ft_strlen(env->buff.buff);
	print_buffer(&env->buff);
	return (TRUE);
}
