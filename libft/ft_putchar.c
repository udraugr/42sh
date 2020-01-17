/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 21:33:47 by wveta             #+#    #+#             */
/*   Updated: 2019/04/15 11:07:00 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	unsigned char	ch;
	char			uni[2];

	ch = (unsigned char)c;
	if (ch < 128)
		write(1, &c, 1);
	else
	{
		uni[0] = (unsigned char)(((ch >> 6) & 31) | 192);
		uni[1] = (unsigned char)((ch & 63) | 128);
		write(1, uni, 2);
	}
}
