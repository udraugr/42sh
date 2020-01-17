/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 20:45:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_check_init(int *i, int *qflag, int *br_c, int *br_f)
{
	*i = 0;
	*qflag = 0;
	*br_c = 0;
	*br_f = 0;
}

void		ft_check_q(int i, int *qflag, char *str, int b_sl)
{
	if (*qflag == 0 && str[i] == '"' && (i == 0 || b_sl == 0))
		*qflag = 1;
	else if (*qflag == 0 && str[i] == '\'' && (i == 0 || b_sl == 0))
		*qflag = 2;
	else if ((*qflag == 1 && str[i] == '"' && (i == 0 || b_sl == 0)) ||
	(*qflag == 2 && str[i] == '\'' && (i == 0 || b_sl == 0)))
		*qflag = 0;
}

void		ft_check_b(int i, char *str, int *br_flag, int *br_count)
{
	if (*br_flag == 0 &&
		((str[i] == '(' && ((*br_flag = 3))) ||
		(str[i] == '{' && ((*br_flag = 4)))))
		*br_count = *br_count + 1;
	else if ((*br_flag == 3 && str[i] == '(') ||
			(*br_flag == 4 && str[i] == '{'))
		*br_count = *br_count + 1;
	else if ((*br_flag == 3 && str[i] == ')') ||
			(*br_flag == 4 && str[i] == '}'))
	{
		*br_count = *br_count - 1;
		if (*br_count == 0)
			*br_flag = 0;
	}
}

int			ft_check_ekran(char *str, int pos)
{
	int i;
	int qflag;
	int br_count;
	int br_flag;
	int	b_sl;

	ft_check_init(&i, &qflag, &br_count, &br_flag);
	b_sl = 0;
	while (str && i < pos && str[i])
	{
		if (qflag != 2 && i > 0 && str[i - 1] && str[i] != '\\' && b_sl == 1)
			b_sl = 0;
		if (qflag != 2 && str[i] == '\\' && ((b_sl = b_sl + 1)))
			b_sl = b_sl % 2;
		ft_check_q(i, &qflag, str, b_sl);
		if (qflag == 0)
			ft_check_b(i, str, &br_flag, &br_count);
		i++;
	}
	if (qflag == 0 && br_flag == 0 && b_sl == 0)
		return (0);
	return (qflag + b_sl);
}

int			ft_check_ekran_full(char *str, int pos)
{
	int i;
	int qflag;
	int br_count;
	int br_flag;
	int	b_sl;

	ft_check_init(&i, &qflag, &br_count, &br_flag);
	b_sl = 0;
	while (str && i < pos && str[i])
	{
		if (qflag != 2 && i > 0 && str[i - 1] && str[i] != '\\' && b_sl == 1)
			b_sl = 0;
		if (qflag != 2 && str[i] == '\\' && ((b_sl = b_sl + 1)))
			b_sl = b_sl % 2;
		ft_check_q(i, &qflag, str, b_sl);
		if (qflag == 0)
			ft_check_b(i, str, &br_flag, &br_count);
		i++;
	}
	return (qflag + b_sl + br_flag);
}
