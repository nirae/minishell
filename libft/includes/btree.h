/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:14:55 by ndubouil          #+#    #+#             */
/*   Updated: 2018/09/14 16:26:31 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "libft.h"

typedef struct		s_btree
{
	void			*data;
	struct s_btree	*parent;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree				*ft_btree_create_node(void *data);
void				ft_btree_insert_data(t_btree **tree, t_btree **parent,
						void *data, int (*cmpf)(void *, void *));
void				*ft_btree_search_item(t_btree *tree, void *ref,
						int (*cmpf)(void *, void *));
void				ft_btree_del(t_btree *tree, void (*del)(void *));
void				ft_btree_apply_prefix(t_btree *tree, void (*func)(void *));
void				ft_btree_apply_infix(t_btree *tree, void (*func)(void *));
void				ft_btree_apply_rev_infix(t_btree *tree,
						void (*func)(void *));
void				ft_btree_apply_suffix(t_btree *tree, void (*func)(void *));
int					ft_btree_nodes_count(t_btree *tree);
int					ft_btree_level_count(t_btree *tree);
t_btree				*left_rotation(t_btree *tree, t_btree *node);

#endif
