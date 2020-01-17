/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:39:27 by wveta             #+#    #+#             */
/*   Updated: 2019/04/08 16:13:20 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *str, int ini, size_t len)
{
	unsigned char	*dest;

	dest = (unsigned char *)str;
	while (len > 0)
	{
		*dest = ini;
		len--;
		dest++;
	}
	return (str);
}
