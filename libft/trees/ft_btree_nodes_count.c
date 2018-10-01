/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_nodes_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:44:57 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:45:43 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

int			ft_btree_nodes_count(t_btree *tree)
{
	if (tree == NULL)
		return (0);
	return (ft_btree_nodes_count(tree->left) + ft_btree_nodes_count(tree->right)
		+ 1);
}
