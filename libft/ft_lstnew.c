/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 08:37:56 by ndubouil          #+#    #+#             */
/*   Updated: 2017/12/14 09:23:29 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*result;

	if (!(result = ft_memalloc(sizeof(*result))))
		return (0);
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		if (!(result->content = malloc(sizeof(*content) * content_size)))
		{
			free(result);
			return (NULL);
		}
		ft_memcpy(result->content, content, content_size);
		result->content_size = content_size;
	}
	result->next = NULL;
	return (result);
}
