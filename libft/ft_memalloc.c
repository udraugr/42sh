/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:21:17 by wveta             #+#    #+#             */
/*   Updated: 2019/04/09 18:43:17 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem;

	if (size > 0)
	{
		mem = malloc(size);
		if (mem != NULL)
		{
			mem = ft_memset(mem, 0, size);
			return (mem);
		}
	}
	return (NULL);
}
