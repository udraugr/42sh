/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:34:27 by wveta             #+#    #+#             */
/*   Updated: 2019/04/12 13:44:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*src;
	size_t			i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	src = (char *)s;
	while (i < n)
	{
		if (*src == (char)ch)
			return ((void *)src);
		src++;
		i++;
	}
	return (NULL);
}
