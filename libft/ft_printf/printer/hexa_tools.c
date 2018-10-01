/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 21:21:19 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/28 10:32:39 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			print_prefix(t_env *env)
{
	if (env->flags.hash && (ft_strcmp("0", env->types.str) != 0 ||
			env->flags.precision > 1))
	{
		if (env->flags.type == 'X')
			env->len += putstr_in_buffer(&env->buff, "0X");
		else
			env->len += putstr_in_buffer(&env->buff, "0x");
		env->flags.hash = 0;
		env->flags.width -= 2;
	}
}

static int		calc_limit(t_env *env, int len)
{
	int				limit;

	if (env->flags.precision > len)
		len = len + (env->flags.precision - len);
	if (ft_strcmp("0", env->types.str) == 0 && env->flags.precision == 0)
		limit = env->flags.width;
	else
		limit = env->flags.width - len;
	if (env->flags.hash && ft_strcmp("0", env->types.str) != 0)
		limit -= 2;
	return (limit);
}

int				print_width_right_hexa(t_env *env, int len, char c)
{
	int				i;
	int				limit;

	i = -1;
	if ((c == '0' && env->flags.precision < 0) || env->flags.width <= 0)
		print_prefix(env);
	if (env->flags.width <= 0)
		return (FALSE);
	limit = calc_limit(env, len);
	if (c == '0' && env->flags.precision >= 0)
		c = ' ';
	if (env->flags.space && c == '0')
	{
		limit--;
		env->len += putchar_in_buffer(&env->buff, ' ');
	}
	while (++i < limit)
		env->len += putchar_in_buffer(&env->buff, c);
	if (c != '0')
		print_prefix(env);
	return (TRUE);
}

int				print_width_left_hexa(t_env *env, int len, char c)
{
	int				i;
	int				limit;

	i = -1;
	if (env->flags.width <= 0)
		return (FALSE);
	if (env->flags.precision > len)
		len = len + (env->flags.precision - len);
	if (ft_strcmp("0", env->types.str) == 0 && env->flags.precision == 0)
		limit = env->flags.width;
	else
		limit = env->flags.width - len;
	if (env->flags.hash && ft_strcmp("0", env->types.str) != 0)
		limit -= 2;
	while (++i < limit)
		env->len += putchar_in_buffer(&env->buff, c);
	return (TRUE);
}
