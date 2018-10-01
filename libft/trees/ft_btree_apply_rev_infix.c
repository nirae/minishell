/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_rev_infix.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:42:53 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:43:45 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btree_apply_rev_infix(t_btree *tree, void (*func)(void *))
{
	if (tree == NULL)
		return ;
	if (tree->right != NULL)
		ft_btree_apply_rev_infix(tree->right, func);
	(*func)((void *)tree);
	if (tree->left != NULL)
		ft_btree_apply_rev_infix(tree->left, func);
}
