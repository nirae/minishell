/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 00:39:59 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/28 10:34:53 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		print_string_with_precision(t_env *env, int len)
{
	int				i;

	i = (env->flags.precision - len);
	if ((ft_strcmp(env->types.str, "0") == 0) && env->flags.precision == 0)
		return (TRUE);
	if (!env->flags.zero && env->flags.hash)
		print_prefix(env);
	if (env->flags.precision > len)
	{
		while (i > 0)
		{
			env->len += putchar_in_buffer(&env->buff, '0');
			i--;
		}
	}
	env->len += putstr_in_buffer(&env->buff, env->types.str);
	return (TRUE);
}

static void		get_str(t_env *env, char ref[16])
{
	if (env->flags.size == H)
		env->types.str = ft_ulli_itoa_base((unsigned short)
			va_arg(env->va, int), ref);
	else if (env->flags.size == HH)
		env->types.str = ft_ulli_itoa_base((unsigned char)
			va_arg(env->va, int), ref);
	else if (env->flags.size == L)
		env->types.str = ft_ulli_itoa_base(
			va_arg(env->va, unsigned long int), ref);
	else if (env->flags.size == LL)
		env->types.str = ft_ulli_itoa_base(
			va_arg(env->va, unsigned long long int), ref);
	else if (env->flags.size == J)
		env->types.str = ft_ulli_itoa_base(va_arg(env->va, uintmax_t), ref);
	else if (env->flags.size == Z)
		env->types.str = ft_ulli_itoa_base((unsigned long long)
			va_arg(env->va, unsigned long long int), ref);
	else
		env->types.str = ft_ulli_itoa_base(va_arg(env->va, unsigned int), ref);
}

static int		get_number(t_env *env)
{
	char	ref[16];

	if (env->flags.type == 'X')
		ft_strcpy(ref, "0123456789ABCDEF");
	else
		ft_strcpy(ref, "0123456789abcdef");
	get_str(env, ref);
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
		}
		print_width_right_hexa(env, len, '0');
	}
	else
		print_width_right_hexa(env, len, ' ');
}

/*
**	Printer for flag "x"
*/

int				print_hexa(t_env *env)
{
	int					len;

	if (!(get_number(env)))
		return (MALLOC_FAIL);
	len = ft_strlen(env->types.str);
	if (env->flags.align == RIGHT)
		padding_right(env, len);
	if (env->flags.space && !env->flags.sign && !env->flags.width)
		env->len += putchar_in_buffer(&env->buff, ' ');
	print_string_with_precision(env, len);
	if (env->flags.align == LEFT)
		print_width_left_hexa(env, len, ' ');
	ft_strdel(&env->types.str);
	return (TRUE);
}
