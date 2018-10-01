/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:40:33 by ndubouil          #+#    #+#             */
/*   Updated: 2018/08/29 18:41:05 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree		*ft_btree_create_node(void *data)
{
	t_btree		*tree;

	if (!(tree = ft_memalloc(sizeof(t_btree))))
		return (NULL);
	tree->parent = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->data = data;
	return (tree);
}
