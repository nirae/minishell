/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_varenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:18:42 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/15 00:23:50 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varenv	*create_varenv(char *name, char *content)
{
	t_varenv	*varenv;

	// Gerer l'erreur
	if (!(varenv = ft_memalloc(sizeof(t_varenv *) + (sizeof(char *) * 2))))
		error();
	if (!(varenv->name = ft_strdup(name)))
		error();
	if (!content)
		varenv->content = NULL;
	else if (!(varenv->content = ft_strdup(content)))
		error();
	return (varenv);
}
