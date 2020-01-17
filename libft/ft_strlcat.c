/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:42:01 by wveta             #+#    #+#             */
/*   Updated: 2019/04/10 23:18:31 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dlen;
	size_t		slen;
	char		*d1;

	slen = ft_strlen(src);
	d1 = dst;
	dlen = size;
	if (dlen > ft_strlen(d1))
		dlen = ft_strlen(d1);
	if (dlen == size)
		return (size + slen);
	if (slen < size - dlen)
	{
		ft_memcpy(d1 + dlen, src, slen);
		d1[dlen + slen] = '\0';
	}
	else
	{
		ft_memcpy(d1 + dlen, src, size - ft_strlen(d1) - 1);
		d1[size - 1] = '\0';
	}
	return (dlen + slen);
}
