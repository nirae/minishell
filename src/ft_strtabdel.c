/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:06:27 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/15 23:25:49 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strtabdel(char ***tab)
{
	int 	i;

	i = -1;
	while ((*tab)[++i])
	{
		// ft_printf("avant free i = %d, str = %s\n", i, tab[i]);
		ft_strdel(&(*tab)[i]);
		// free(tab[i]);
		// ft_printf("apres free i = %d, str = %s\n", i, (*tab)[i]);
	}
	// free(tab);
	// tab = NULL;
	// ft_printf("avant dernier free i = %d, str = %s\n", i, (*tab)[i]);
	ft_strdel(&(*tab)[i]);
	// ft_printf("apres dernier free i = %d, str = %s\n", i, (*tab)[i]);
	ft_memdel((void **)tab);
	// ft_printf("test si free bon = %s\n", (*tab)[0]);
}
