/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:30:31 by ndubouil          #+#    #+#             */
/*   Updated: 2017/11/22 14:05:47 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_calcul_nb(int nb)
{
	if (nb >= 10 || nb <= -10)
	{
		ft_calcul_nb(nb / 10);
		ft_calcul_nb(nb % 10);
	}
	else if (nb >= 0)
		ft_putchar(nb + 48);
	else
		ft_putchar(48 - nb);
}

void			ft_putnbr(int n)
{
	if (!ft_ispositive(n))
	{
		ft_putchar('-');
		ft_calcul_nb(n);
	}
	else
		ft_calcul_nb(n);
}
