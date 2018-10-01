/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:43:20 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:43:48 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btree_apply_suffix(t_btree *tree, void (*func)(void *))
{
	if (tree == NULL)
		return ;
	if (tree->left != NULL)
		ft_btree_apply_suffix(tree->left, func);
	if (tree->right != NULL)
		ft_btree_apply_suffix(tree->right, func);
	(*func)((void *)tree);
}
