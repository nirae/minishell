/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 21:07:13 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 19:22:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		print_width(t_env *env, int len)
{
	int				i;

	i = -1;
	if (env->flags.precision >= 0 && len > env->flags.precision)
		while (++i < env->flags.width - env->flags.precision)
			env->len += putchar_in_buffer(&env->buff, ' ');
	else
		while (++i < env->flags.width - len)
			env->len += putchar_in_buffer(&env->buff, ' ');
}

static void		print_string_with_precision(t_env *env, int len)
{
	int				i;

	i = -1;
	if (env->flags.precision >= 0)
	{
		while (++i < env->flags.precision && i < len)
			env->len += putchar_in_buffer(&env->buff, env->types.str[i]);
	}
	else
		env->len += putstr_in_buffer(&env->buff, env->types.str);
}

/*
** Printer for flag 's'
*/

int				print_string(t_env *env)
{
	char			nullstr[7];
	int				len;

	ft_strcpy(nullstr, "(null)");
	if ((env->types.str = va_arg(env->va, char *)) == NULL)
		env->types.str = nullstr;
	len = ft_strlen(env->types.str);
	if (env->flags.width >= 1)
	{
		if (env->flags.align == RIGHT)
			print_width(env, len);
		print_string_with_precision(env, len);
		if (env->flags.align == LEFT)
			print_width(env, len);
		return (TRUE);
	}
	print_string_with_precision(env, len);
	return (TRUE);
}
