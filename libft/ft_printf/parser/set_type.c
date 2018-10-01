/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 09:22:15 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:20:40 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Type setter
** Take the string, check if there is a valid flag and fill struct t_flags
** Return TRUE when finished or FALSE if no flags found
*/

int		set_type(char *str, t_env *env)
{
	if (!is_valid_type(str[env->pos]))
		return (FALSE);
	env->flags.type = str[env->pos];
	env->pos++;
	return (TRUE);
}
