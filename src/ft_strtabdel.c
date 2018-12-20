/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:06:27 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 03:56:36 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strtabdel(char ***tab)
{
	int		i;

	if (!*tab || !(*tab)[0])
		return ;
	i = -1;
	while ((*tab)[++i])
		ft_strdel(&(*tab)[i]);
	ft_strdel(&(*tab)[i]);
	ft_memdel((void **)tab);
	*tab = NULL;
}
