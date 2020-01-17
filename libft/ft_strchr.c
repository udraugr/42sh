/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:14:35 by wveta             #+#    #+#             */
/*   Updated: 2019/04/22 16:16:04 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (!(s))
		return (NULL);
	ch = (unsigned char)c;
	while (*s != '\0' || !c)
	{
		if (*s == (char)ch)
			return ((char *)s);
		s++;
	}
	if (*s == (char)ch)
		return ((char *)s);
	return (NULL);
}
