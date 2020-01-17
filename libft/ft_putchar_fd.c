/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:11:43 by wveta             #+#    #+#             */
/*   Updated: 2019/04/15 11:16:20 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	ch;
	char			uni[2];

	ch = (unsigned char)c;
	if (ch < 128)
		write(fd, &c, 1);
	else
	{
		uni[0] = (unsigned char)(((ch >> 6) & 31) | 192);
		uni[1] = (unsigned char)((ch & 63) | 128);
		write(fd, uni, 2);
	}
}
