/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:41:25 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:43:42 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btree_apply_prefix(t_btree *tree, void (*func)(void *))
{
	if (tree == NULL)
		return ;
	(*func)((void *)tree);
	if (tree->left != NULL)
		ft_btree_apply_prefix(tree->left, func);
	if (tree->right != NULL)
		ft_btree_apply_prefix(tree->right, func);
}
