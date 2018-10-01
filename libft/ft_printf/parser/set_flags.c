/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:37:23 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:40:13 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Flags setter
**
** Take the string, check until flags don't match and fill struct t_flags
** Work with flags '-' '+' '0' ' ' '#'
** Return TRUE when finished
*/

int		set_flags(char *str, t_env *env)
{
	if (!is_valid_flags(str[env->pos]))
		return (TRUE);
	if (str[env->pos] == '-')
	{
		env->flags.align = LEFT;
		env->flags.zero = FALSE;
	}
	if (str[env->pos] == '+')
	{
		env->flags.sign = TRUE;
		env->flags.space = FALSE;
	}
	if (str[env->pos] == '0' && env->flags.align != LEFT)
		env->flags.zero = TRUE;
	if (str[env->pos] == ' ' && !env->flags.sign)
		env->flags.space = TRUE;
	if (str[env->pos] == '#')
		env->flags.hash = TRUE;
	env->pos++;
	return (set_flags(str, env));
}
