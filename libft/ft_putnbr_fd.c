/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:15:19 by wveta             #+#    #+#             */
/*   Updated: 2019/04/10 22:16:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int a;
	int b;

	if (nb == -2147483648)
	{
		ft_putnbr_fd(-214748364, fd);
		ft_putchar_fd('8', fd);
	}
	else
	{
		if (nb < 0)
		{
			nb = nb * (-1);
			ft_putchar_fd('-', fd);
		}
		a = nb / 10;
		b = nb % 10;
		if (a > 0)
			ft_putnbr_fd(a, fd);
		ft_putchar_fd(b + 48, fd);
	}
}
