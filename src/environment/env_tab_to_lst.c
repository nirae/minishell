/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab_to_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 21:15:34 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/18 21:15:37 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_tab_to_lst(t_list **lst, char **environ)
{
	int		i;
	t_list	*tmplst;
	char	**env;
	int		pos;

	if (environ[0] == NULL)
		return (FALSE);
	i = 0;
	while (environ[i])
	{
		if (!(tmplst = ft_lstnew(NULL, sizeof(t_varenv *))))
			return (FALSE);
		if (!(env = ft_strsplit(environ[i], '=')))
		 	return (FALSE);
		pos = ft_strpos(environ[i], '=');
		tmplst->content = create_varenv(env[0], &environ[i][pos + 1]);
		if (!(*lst))
			*lst = tmplst;
		else
			ft_lstaddend(lst, tmplst);
		ft_strtabdel(&env);
		i++;
	}
	return (TRUE);
}
