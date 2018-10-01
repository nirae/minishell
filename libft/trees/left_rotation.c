/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:46:34 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:46:24 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*left_rotation(t_btree *tree, t_btree *node)
{
	t_btree *tmp;

	tmp = node->right;
	node->right = tmp->left;
	if (tmp->left != NULL)
		tmp->left->parent = node;
	tmp->parent = node->parent;
	if (node->parent == NULL)
		tree = tmp;
	else if (node == node->parent->left)
		node->parent->left = tmp;
	else
		node->parent->right = tmp;
	tmp->left = node;
	node->parent = tmp;
	return (tree);
}
