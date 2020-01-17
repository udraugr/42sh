/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:47:55 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 19:17:53 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char *s1, char *s2, int len)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (s1)
	{
		while (s1[i] && i < len)
		{
			ret[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j] && i < len)
			ret[i++] = s2[j++];
	}
	ret[i] = '\0';
	return (ret);
}
