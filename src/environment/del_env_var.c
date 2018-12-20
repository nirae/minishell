/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:41:44 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/19 20:31:38 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_env_var(void *content, size_t size)
{
	(void)size;
	ft_strdel(&((t_varenv *)(content))->name);
	ft_strdel(&((t_varenv *)(content))->content);
	ft_memdel(&content);
}
