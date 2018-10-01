/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:44:02 by ndubouil          #+#    #+#             */
/*   Updated: 2018/08/29 18:44:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btree_insert_data(t_btree **tree, t_btree **parent, void *data,
				int (*cmpf)(void *, void *))
{
	if (*tree == NULL)
	{
		*tree = ft_btree_create_node(data);
		(*tree)->parent = *parent;
	}
	else
	{
		if ((*cmpf)(data, (*tree)->data) <= 0)
			ft_btree_insert_data(&(*tree)->left, tree, data, cmpf);
		else
			ft_btree_insert_data(&(*tree)->right, tree, data, cmpf);
	}
}
