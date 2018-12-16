/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:42:39 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/16 16:58:12 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		final_return(char **s, int n_lus)
{
	int		i;
	char	*temp;

	// VOIR POUR CONTROL D ET LE CATCH
	if (n_lus == 0 && *s == 0)
	{
		ft_strdel(s);
		return (0);
	}
	if (ft_strpos(*s, '\n') == (int)ft_strlen(*s))
		i = 0;
	else
		i = 1;
	temp = *s;
	*s = ft_strsub(temp, ft_strpos(temp, '\n') + i, (int)ft_strlen(temp));
	ft_strdel(&temp);
	ft_strdel(s);
	return (1);
}

int				read_prompt(const int fd, char **line)
{
	char				*buff;
	char				*final_buff;
	int					n_lus;

	if (BUFF_SIZE <= 0 || (n_lus = read(fd, "", 0)) == -1)
		return (-1);
	if (!(buff = ft_strnew(4096)))
		return (-1);
	// if (!(final_buff = ft_strnew(0)))
	// 	return (-1);
	final_buff = NULL;
	while (!ft_strchr(final_buff, '\n') && (n_lus = read(fd, buff, 4096)) > 0)
	{
		if (!final_buff)
			final_buff = ft_strdup(buff);
		else
			final_buff = ft_strjoin(final_buff, buff);
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	*line = ft_strsub(final_buff, 0, ft_strpos(final_buff, '\n'));
	return (final_return(&final_buff, n_lus));
}
