/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:42:39 by ndubouil          #+#    #+#             */
/*   Updated: 2018/11/21 19:28:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		final_return(char **s, int n_lus)
{
	int		i;
	char	*temp;

	if (n_lus == 0 && **s == 0)
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

// void			clean_fd(int fd)
// {
// 	int 		n_lus;
// 	char		*buff;
// 	char		*bigbuff;
//
// 	if (!(buff = ft_strnew(4096)))
// 		return;
// 	if (!(bigbuff = ft_strnew(0)))
// 		return;
// 	while (ft_strchr(bigbuff, '\n'))
// 	{
// 		while (!ft_strchr(bigbuff, '\n') && (n_lus = read(fd, buff, 4096)) > 0)
// 		{
// 			ft_printf("buff = %s\n", buff);
// 			bigbuff = ft_strjoin(bigbuff, buff);
// 			ft_strclr(buff);
// 		}
// 	}
// }

int				read_prompt(const int fd, char **line, int option)
{
	char				*buff;
	char			*final_buff;
	int					n_lus;
	// char				*temp;

	(void)option;
	// if (option == 1)
	// {
	// 	*line = ft_strdup(final_buff);
	// 	//ft_printf("reste: %s\n", final_buff);
	// 	ft_strclr(final_buff);
	// 	return (1);
	// }
	// else if (option == 2)
	// {
	// 	ft_strclr(final_buff);
	// 	return (1);
	// }
	if (BUFF_SIZE <= 0 || (n_lus = read(fd, "", 0)) == -1)
		return (-1);
	if (!(buff = ft_strnew(4096)))
		return (-1);
	if (!(final_buff = ft_strnew(0)))
		return (-1);
	//ft_strclr(*line);
	//ft_strclr(buff);
	//ft_strclr(final_buff);
	while (!ft_strchr(final_buff, '\n') && (n_lus = read(fd, buff, 4096)) > 0)
	{
		ft_printf("buff = %s\n", buff);
		final_buff = ft_strjoin(final_buff, buff);
		ft_strclr(buff);
	}
	// clean_fd(fd);
	ft_strdel(&buff);
	ft_printf("final_buff = %s\n", final_buff);
	*line = ft_strsub(final_buff, 0, ft_strpos(final_buff, '\n'));
	return (final_return(&final_buff, n_lus));
}
