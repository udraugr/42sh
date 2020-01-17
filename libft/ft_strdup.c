/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 12:57:59 by wveta             #+#    #+#             */
/*   Updated: 2019/04/05 13:31:33 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*d;
	size_t	len;
	size_t	j;

	len = 0;
	j = 0;
	len = ft_strlen(s1);
	d = (char *)malloc(len + 1);
	if (d == NULL)
		return (NULL);
	while (j < len)
	{
		d[j] = s1[j];
		j++;
	}
	d[j] = '\0';
	return (d);
}
