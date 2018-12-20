/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_addend_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:41:33 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/20 02:34:49 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_realloc_addend_tab(char ***tab, char *elem)
{
	int		i;
	char	**tmp;

	if (*tab == NULL || !elem)
		return (FALSE);
	i = -1;
	while ((*tab)[++i])
		;
	if (!(tmp = ft_memalloc((i + 2) * sizeof(char *))))
		return (FALSE);
	i = -1;
	while ((*tab)[++i])
		if (!(tmp[i] = ft_strdup((*tab)[i])))
			return (FALSE);
	if (!(tmp[i] = ft_strdup(elem)))
		return (FALSE);
	tmp[i + 1] = NULL;
	ft_strtabdel(tab);
	*tab = tmp;
	return (TRUE);
}
