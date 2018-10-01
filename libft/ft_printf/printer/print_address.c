/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 19:54:58 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/26 22:20:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		print_width(t_env *env, int len)
{
	int				i;

	i = -1;
	while (++i < env->flags.width - len)
		env->len += putchar_in_buffer(&env->buff, ' ');
}

/*
** Printer for flag 'p'
*/

int				print_address(t_env *env)
{
	int			i;
	int			len;

	i = -1;
	env->types.ulli = (long long int)va_arg(env->va, void *);
	env->types.str = ft_lli_itoa_base(env->types.ulli, "0123456789abcdef");
	if (env->types.str == NULL)
		return (FALSE);
	len = ft_strlen(env->types.str) + 2;
	if (env->flags.width > 0)
	{
		if (env->flags.align == RIGHT)
			print_width(env, len);
		env->len += putstr_in_buffer(&env->buff, "0x");
		env->len += putstr_in_buffer(&env->buff, env->types.str);
		if (env->flags.align == LEFT)
			print_width(env, len);
		return (TRUE);
	}
	env->len += putstr_in_buffer(&env->buff, "0x");
	env->len += putstr_in_buffer(&env->buff, env->types.str);
	ft_strdel(&env->types.str);
	return (TRUE);
}
