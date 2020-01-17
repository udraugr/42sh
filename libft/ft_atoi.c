/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:34:35 by wveta             #+#    #+#             */
/*   Updated: 2019/04/11 21:52:16 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int				ft_space(char st)
{
	if (st != '\0' && (st == ' ' || st == '\n' || st == '\t' ||
		st == '\r' || st == '\v' || st == '\f'))
		return (1);
	return (0);
}

static	int				ft_tst_numb(char st)
{
	if (st != '\0' && (st == '+' || st == '-' || (st >= '0' && st <= '9')))
		return (1);
	return (0);
}

static int				ft_set_flag(char s, int *flag)
{
	if (*flag == 0)
	{
		if (s == '+')
			*flag = 1;
		else
			*flag = -1;
		return (0);
	}
	return (1);
}

static int				ft_ower(unsigned long int rez, char s, int sign)
{
	if ((rez > 922337203685477580 ||
		(rez == 922337203685477580
		&& (s - 48) > 7)) && sign == 1)
		return (-1);
	else if ((rez > 922337203685477580 ||
			(rez == 922337203685477580
			&& (s - 48) > 8)) && sign == -1)
		return (0);
	return (1);
}

int						ft_atoi(const char *str)
{
	unsigned long int	rez;
	int					flag;

	rez = 0;
	flag = 0;
	while (ft_space(*str) == 1 && *str != '\0')
		str++;
	while (ft_tst_numb(*str) == 1 && *str != '\0')
	{
		if ((*str == '+' || *str == '-') && (ft_set_flag(*str, &flag) == 1))
			return ((int)rez * flag);
		else if (*str >= '0' && *str <= '9')
		{
			if (flag == 0)
				flag = 1;
			if (ft_ower(rez, *str, flag) == 1)
				rez = rez * 10 + (*str - 48);
			else
				return (ft_ower(rez, *str, flag));
		}
		str++;
	}
	return ((int)rez * flag);
}
