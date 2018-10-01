/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:12:31 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/24 18:04:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** Initialisation of all flags in struct t_flags
**
** By Default :
** 		Align - : right
**		Sign + : false
**		Zero 0 : false
**		Space ' ' : false
**		Hash # : false
**		Width XXX: zero
**		Precision .XXX : zero
**		Size l ll h hh j z none : false
*/

void	init_flags(t_env *env)
{
	env->flags.align = RIGHT;
	env->flags.sign = FALSE;
	env->flags.zero = FALSE;
	env->flags.space = FALSE;
	env->flags.hash = FALSE;
	env->flags.width = 0;
	env->flags.precision = 0;
	env->flags.size = FALSE;
	env->flags.type = FALSE;
}
