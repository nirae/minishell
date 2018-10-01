/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 23:25:48 by ndubouil          #+#    #+#             */
/*   Updated: 2018/06/26 23:26:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		parser(char *str, t_env *env)
{
	init_flags(env);
	set_flags(str, env);
	set_width(str, env);
	set_precision(str, env);
	set_size(str, env);
	if (!set_type(str, env))
		return (FALSE);
	return (TRUE);
}
