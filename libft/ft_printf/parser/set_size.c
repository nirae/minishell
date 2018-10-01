/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:12:18 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:19:33 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Size setter
** Take the string, check if there is a valid flag and fill struct t_flags
** Work with h hh l ll j z
** Return TRUE when finished or FALSE if no flags found
*/

int		set_size(char *str, t_env *env)
{
	if (!is_valid_sizeflag(str[env->pos]))
		return (FALSE);
	if (str[env->pos] == 'h')
		env->flags.size = H;
	else if (str[env->pos] == 'l')
		env->flags.size = L;
	else if (str[env->pos] == 'j')
		env->flags.size = J;
	else if (str[env->pos] == 'z')
		env->flags.size = Z;
	env->pos++;
	if (env->flags.size == H && str[env->pos] == 'h')
	{
		env->flags.size = HH;
		env->pos++;
	}
	else if (env->flags.size == L && str[env->pos] == 'l')
	{
		env->flags.size = LL;
		env->pos++;
	}
	return (TRUE);
}
