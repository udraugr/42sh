/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:35:17 by wveta             #+#    #+#             */
/*   Updated: 2019/04/16 08:50:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char *d;
	char *s;
	char *final_d;
	char *final_s;

	if (dest == src)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		final_d = d + len - 1;
		final_s = s + len - 1;
		while (len--)
			*final_d-- = *final_s--;
	}
	return (dest);
}
