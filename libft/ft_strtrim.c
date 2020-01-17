/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:27:15 by wveta             #+#    #+#             */
/*   Updated: 2019/04/12 17:52:38 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*ret;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	j = 0;
	while (s[j] != '\0' && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j++;
	i = ft_strlen(s) - 1;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	if (i == -1)
		j = 0;
	ret = (char *)malloc(sizeof(char) * (2 + i - j));
	if (ret == NULL)
		return (NULL);
	if ((1 + i - j) > 0)
		ret = ft_strncpy(ret, s + j, (size_t)(1 + i - j));
	ret[1 + i - j] = '\0';
	return (ret);
}
