/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:06:27 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 21:31:32 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strtabdel(char ***tab)
{
	int 	i;

	i = -1;
	while ((*tab)[++i])
		ft_strdel(&(*tab)[i]);
	ft_strdel(&(*tab)[i]);
	ft_memdel((void **)tab);
}
