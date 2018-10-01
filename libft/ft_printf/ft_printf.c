/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 09:38:44 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/27 12:58:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		check_string(t_env *env, char *string)
{
	int		ret;

	while (string[env->pos] != 0)
	{
		if (string[env->pos] != '%')
		{
			env->len += putchar_in_buffer(&env->buff, string[env->pos]);
			env->pos++;
			continue;
		}
		env->pos++;
		if (!parser(string, env))
		{
			print_buffer(&env->buff);
			return (FAIL);
		}
		ret = printer(env);
		if (ret == FAIL)
			return (-1);
		else if (ret == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	return (TRUE);
}

int		ft_printf(const char *str, ...)
{
	t_env		env;
	char		*string;
	int			ret;

	va_start(env.va, str);
	string = (char *)str;
	env.pos = 0;
	env.len = 0;
	env.buff.len = 0;
	env.buff.pos_last_conv = 0;
	ret = check_string(&env, string);
	if (ret == FAIL)
		return (-1);
	else if (ret == MALLOC_FAIL)
		return (MALLOC_FAIL);
	va_end(env.va);
	print_buffer(&env.buff);
	return (env.len);
}
