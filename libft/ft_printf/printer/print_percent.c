/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 23:22:41 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/26 23:23:02 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		print_percent(t_env *env)
{
	long long int		i;

	i = -1;
	env->types.c = '%';
	if (env->flags.width > 1)
	{
		if (env->flags.align == RIGHT)
			while (++i < env->flags.width - 1)
			{
				if (env->flags.zero)
					env->len += putchar_in_buffer(&env->buff, '0');
				else
					env->len += putchar_in_buffer(&env->buff, ' ');
			}
		env->len += putchar_in_buffer(&env->buff, env->types.c);
		if (env->flags.align == LEFT)
			while (++i < env->flags.width - 1)
				env->len += putchar_in_buffer(&env->buff, ' ');
		return (TRUE);
	}
	env->len += putchar_in_buffer(&env->buff, env->types.c);
	return (TRUE);
}
