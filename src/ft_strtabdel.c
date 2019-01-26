/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:06:27 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/26 22:29:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strtabdel(char ***tab)
{
	int		i;

	if (!(*tab))
		return ;
	if (!(*tab)[0])
	{
		ft_memdel((void **)tab);
		*tab = NULL;
		return ;
	}
	i = -1;
	while ((*tab)[++i])
		ft_strdel(&(*tab)[i]);
	ft_strdel(&(*tab)[i]);
	ft_memdel((void **)tab);
	*tab = NULL;
}
