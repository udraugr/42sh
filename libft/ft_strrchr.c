/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:04:38 by wveta             #+#    #+#             */
/*   Updated: 2019/04/12 15:51:02 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char				*src;
	char				*ptr;
	unsigned char		ch;

	ptr = NULL;
	src = (char *)s;
	ch = (unsigned char)c;
	while (*src != '\0')
	{
		if (*src == (char)ch)
			ptr = (char *)src;
		src++;
	}
	if (*src == (char)ch)
		ptr = (char *)src;
	return (ptr);
}
