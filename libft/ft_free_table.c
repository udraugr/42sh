/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:27:53 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 15:41:33 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_table(char ***table)
{
	char	**tmp;
	int		i;

	if (!table || !*table)
		return ;
	i = -1;
	tmp = *table;
	while (tmp[++i])
		ft_memdel((void**)&tmp[i]);
	ft_memdel((void**)table);
}
