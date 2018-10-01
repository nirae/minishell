/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 22:17:55 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/26 22:04:20 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		print_width(t_env *env, int len, char c)
{
	int				i;
	int				limit;

	i = -1;
	if (env->flags.width == 0)
		return (FALSE);
	if (env->flags.precision > len)
		len += (env->flags.precision - len);
	if (env->types.str[0] == '-' && env->flags.precision > (len - 1))
		len++;
	limit = env->flags.width - len;
	if ((env->flags.sign == 1 && env->types.str[0] != '-'))
		limit--;
	if (env->flags.space && c == '0')
	{
		limit--;
		env->len += putchar_in_buffer(&env->buff, ' ');
	}
	if ((ft_strcmp(env->types.str, "0") == 0) && env->flags.precision == 0)
		env->len += putchar_in_buffer(&env->buff, ' ');
	while (++i < limit)
		env->len += putchar_in_buffer(&env->buff, c);
	return (TRUE);
}

static int		print_string_with_precision(t_env *env, int len)
{
	int				i;

	i = (env->flags.precision - len);
	if ((ft_strcmp(env->types.str, "0") == 0) && env->flags.precision == 0)
		return (0);
	if (env->types.str[0] == '-')
	{
		env->len += putchar_in_buffer(&env->buff, '-');
		ft_strcpy(env->types.str, &env->types.str[1]);
		i++;
	}
	if (env->flags.precision > len)
	{
		while (i > 0)
		{
			env->len += putchar_in_buffer(&env->buff, '0');
			i--;
		}
	}
	env->len += putstr_in_buffer(&env->buff, env->types.str);
	return (0);
}

static int		get_number(t_env *env)
{
	if (env->flags.size == H)
		env->types.str =
			ft_lli_itoa_base((short)va_arg(env->va, int), "0123456789");
	else if (env->flags.size == HH)
		env->types.str =
			ft_lli_itoa_base((char)va_arg(env->va, int), "0123456789");
	else if (env->flags.size == L || env->flags.type == 'D')
		env->types.str =
			ft_lli_itoa_base(va_arg(env->va, long int), "0123456789");
	else if (env->flags.size == LL)
		env->types.str =
			ft_lli_itoa_base(va_arg(env->va, long long int), "0123456789");
	else if (env->flags.size == J)
		env->types.str =
			ft_lli_itoa_base(va_arg(env->va, intmax_t), "0123456789");
	else if (env->flags.size == Z)
		env->types.str =
			ft_lli_itoa_base(va_arg(env->va, size_t), "0123456789");
	else
		env->types.str =
			ft_lli_itoa_base(va_arg(env->va, int), "0123456789");
	if (env->types.str == NULL)
		return (FALSE);
	return (TRUE);
}

static void		padding_right(t_env *env, int len)
{
	if (env->flags.zero && env->flags.precision <= len)
	{
		if (env->types.str[0] == '-')
		{
			env->len += putchar_in_buffer(&env->buff, '-');
			ft_strcpy(env->types.str, &env->types.str[1]);
			env->flags.sign = 0;
		}
		else if (env->flags.sign)
		{
			env->len += putchar_in_buffer(&env->buff, '+');
			env->flags.width--;
			env->flags.sign = 0;
		}
		print_width(env, len, '0');
	}
	else
		print_width(env, len, ' ');
}

/*
**	Printer for flag "d"
*/

int				print_number(t_env *env)
{
	int					len;

	if (!(get_number(env)))
		return (MALLOC_FAIL);
	len = ft_strlen(env->types.str);
	if (env->flags.width < 0)
	{
		env->flags.align = LEFT;
		env->flags.width = -env->flags.width;
	}
	if (env->flags.align == RIGHT)
		padding_right(env, len);
	if (env->flags.space && !env->flags.sign && !env->flags.width
			&& env->types.str[0] != '-')
		env->len += putchar_in_buffer(&env->buff, ' ');
	if (env->flags.sign && env->types.str[0] != '-')
		env->len += putchar_in_buffer(&env->buff, '+');
	print_string_with_precision(env, len);
	if (env->flags.align == LEFT)
		print_width(env, len, ' ');
	ft_strdel(&env->types.str);
	return (TRUE);
}
