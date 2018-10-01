/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:56:35 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/14 10:15:59 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_calcul_nb(int nb, int fd)
{
	if (nb >= 10 || nb <= -10)
	{
		ft_calcul_nb(nb / 10, fd);
		ft_calcul_nb(nb % 10, fd);
	}
	else if (nb >= 0)
		ft_putchar_fd(nb + 48, fd);
	else
		ft_putchar_fd(48 - nb, fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (!ft_ispositive(n))
	{
		ft_putchar_fd('-', fd);
		ft_calcul_nb(n, fd);
	}
	else
		ft_calcul_nb(n, fd);
}
