/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_search_item.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:47:30 by ndubouil          #+#    #+#             */
/*   Updated: 2018/08/29 18:47:58 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		*ft_btree_search_item(t_btree *tree, void *ref,
				int (*cmpf)(void *, void *))
{
	static void *result = NULL;

	if ((*cmpf)(ref, tree->data) == 0)
		return (tree->data);
	if (tree->left != NULL)
		result = ft_btree_search_item(tree->left, ref, cmpf);
	if (tree->right != NULL)
		result = ft_btree_search_item(tree->right, ref, cmpf);
	return (result);
}
