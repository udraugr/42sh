/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:18:19 by wveta             #+#    #+#             */
/*   Updated: 2019/04/10 21:21:53 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_len(int n)
{
	int		i;
	int		l;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	l = 0;
	i = n;
	if (i < 0)
		i = i * (-1);
	while (i > 0)
	{
		i = i / 10;
		l++;
	}
	if (n < 0)
		l++;
	return (l);
}

static char	*ft_set_min(char *ret, int l)
{
	int		n;

	ret[0] = '-';
	l--;
	ret[l] = '8';
	n = 214748364;
	while (n > 0)
	{
		ret[--l] = (n % 10) + 48;
		n = n / 10;
	}
	return (ret);
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		l;

	l = ft_int_len(n);
	if ((ret = (char *)malloc(sizeof(char) * (l + 1))) == NULL)
		return (NULL);
	ret[l] = '\0';
	if (n == -2147483648)
		ret = ft_set_min(ret, l);
	else
	{
		if (n < 0)
		{
			ret[0] = '-';
			n = n * (-1);
		}
		else if (n == 0)
			ret[0] = '0';
		while (n > 0)
		{
			ret[--l] = (n % 10) + 48;
			n = n / 10;
		}
	}
	return (ret);
}
