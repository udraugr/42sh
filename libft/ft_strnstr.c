/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:23:51 by wveta             #+#    #+#             */
/*   Updated: 2019/04/09 13:17:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*ret;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < (int)len)
	{
		ret = (char *)&haystack[i];
		j = 0;
		while (needle[j] && j < (int)len && i + j < (int)len)
		{
			if (haystack[i + j] != needle[j])
				ret = NULL;
			j++;
		}
		if (ret != NULL && needle[j] == '\0')
			return (ret);
		i++;
	}
	return (NULL);
}
