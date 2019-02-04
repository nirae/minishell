/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:42:39 by ndubouil          #+#    #+#             */
/*   Updated: 2019/02/04 04:15:55 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		final_return(char **s, int n_lus)
{
	char	*temp;

	if (n_lus == 0 && !(*s))
	{
		ft_strdel(s);
		return (0);
	}
	temp = *s;
	*s = ft_strsub(temp, ft_strpos(temp, '\n'), (int)ft_strlen(temp));
	ft_strdel(&temp);
	ft_strdel(s);
	return (1);
}

char			*ft_strjoin_free_s1(char **s1, char **s2)
{
	int		i;
	int		j;
	char	*dest;

	if (!(s1) || !(s2))
		return (NULL);
	i = 0;
	j = 0;
	if (!(dest = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2))))
		return (NULL);
	while ((*s1)[i])
	{
		dest[i] = (*s1)[i];
		i++;
	}
	while ((*s2)[j])
	{
		dest[i] = (*s2)[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	ft_strdel(s1);
	return (dest);
}

int				read_prompt(const int fd, char **line)
{
	char		*buff;
	char		*final_buff;
	int			n_lus;

	if ((n_lus = read(fd, "", 0)) == -1)
		return (-1);
	if (!(buff = ft_strnew(1)))
		return (-1);
	final_buff = NULL;
	while (!ft_strchr(final_buff, '\n') && (n_lus = read(fd, buff, 1)) > 0)
	{
		if (!buff[0])
			break ;
		if (!final_buff)
			final_buff = ft_strdup(buff);
		else
			final_buff = ft_strjoin_free_s1(&final_buff, &buff);
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	*line = ft_strsub(final_buff, 0, ft_strpos(final_buff, '\n'));
	return (final_return(&final_buff, n_lus));
}
