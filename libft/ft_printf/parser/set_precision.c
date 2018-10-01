/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:37:19 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:17:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Precision setter
** Take the string, check if there is a '.' and number and fill struct t_flags
** Work also with * flag
** Return TRUE when finished or FALSE if no precision found
*/

int		set_precision(char *str, t_env *env)
{
	int		i;

	i = 0;
	if (str[env->pos] != '.')
	{
		env->flags.precision = -1;
		return (FALSE);
	}
	env->pos++;
	while (ft_isdigit(str[env->pos]))
	{
		i = (str[env->pos] - '0' + i * 10);
		env->pos++;
	}
	if (str[env->pos] == '*')
	{
		i = va_arg(env->va, int);
		if (i < 0)
			i = -1;
		env->pos++;
	}
	env->flags.precision = i;
	return (TRUE);
}
