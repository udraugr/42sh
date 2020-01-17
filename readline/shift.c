/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:42:43 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 18:04:27 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char		*check_shift(char *str)
{
	if (!(ft_strcmp(str, SHIFT_LFT)))
	{
		ft_bzero(str, 20);
		str = ft_strcpy(str, ";2D");
	}
	else if (!(ft_strcmp(str, SHIFT_RGT)))
	{
		ft_bzero(str, 20);
		str = ft_strcpy(str, ";2C");
	}
	else if (!(ft_strcmp(str, SHIFT_UP)))
	{
		ft_bzero(str, 20);
		str = ft_strcpy(str, ";2A");
	}
	else if (!(ft_strcmp(str, SHIFT_DO)))
	{
		ft_bzero(str, 20);
		str = ft_strcpy(str, ";2B");
	}
	else if (str[0] == '\e')
		ft_bzero(str, 20);
	return (str);
}
