/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:21:34 by wveta             #+#    #+#             */
/*   Updated: 2019/04/09 20:48:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (size + 1 < size)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str != NULL)
	{
		str = ft_memset(str, 0, size + 1);
		return (str);
	}
	return (NULL);
}
