/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:42:32 by wveta             #+#    #+#             */
/*   Updated: 2019/12/07 22:12:29 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (s1)
		i = i + ft_strlen(s1);
	if (s2)
		i = i + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	if (s1)
		ret = ft_strcat((char *)ret, (char *)s1);
	if (s2)
		ret = ft_strcat((char *)ret, (char *)s2);
	return (ret);
}
