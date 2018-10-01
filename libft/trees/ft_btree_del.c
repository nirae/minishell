/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:39:14 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:43:54 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btree_del(t_btree *tree, void (*del)(void *))
{
	if (tree == NULL)
		return ;
	ft_btree_del(tree->left, del);
	ft_btree_del(tree->right, del);
	del(tree->data);
	ft_memdel((void **)&tree);
}
