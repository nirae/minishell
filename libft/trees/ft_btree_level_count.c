/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:45:22 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/25 17:45:08 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

int			ft_btree_level_count(t_btree *tree)
{
	int		result;

	if (tree == NULL)
		return (0);
	result = 0;
	if (tree->left != NULL)
	{
		if (result > 0)
			result--;
		result = ft_btree_level_count(tree->left);
	}
	if (tree->right != NULL)
	{
		if (result > 0)
			result--;
		result = ft_btree_level_count(tree->right);
	}
	return (result + 1);
}
