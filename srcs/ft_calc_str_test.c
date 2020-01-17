/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_str_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 12:24:28 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "calc/include/arithmetic.h"

void		ft_cacl_test_b(t_quoteflag *f, char *str)
{
	if ((f->br_flag == 0 || f->br_flag == 1) &&
	str[f->i] == '(' && (f->i == 0 || ft_strchr(" ;|&$", str[f->i - 1])))
	{
		f->br_flag = 1;
		f->br_count = f->br_count + 1;
	}
	else if (f->br_flag == 1 && str[f->i] == '(')
		f->br_count = f->br_count + 1;
	else if ((f->br_flag == 0 || f->br_flag == 2) &&
	str[f->i] == '{' && (f->i == 0 || ft_strchr(" ;|&", str[f->i - 1])))
	{
		f->br_flag = 2;
		f->br_count = f->br_count + 1;
	}
	else if (f->br_flag == 1 && str[f->i] == '{')
		f->br_count = f->br_count + 1;
}

void		ft_calc_test_q(t_quoteflag *f, char *str)
{
	if ((f->qflag == 2 && str[f->i] == '\'') && (f->i == 0 || f->b_sl == 0))
		f->qflag = 0;
	else if (f->qflag == 0 && str[f->i] == '\'' && (f->i == 0 || f->b_sl == 0))
		f->qflag = 2;
}

t_quoteflag	*ft_get_quoteflag(void)
{
	t_quoteflag *f;

	if (!(f = malloc(sizeof(t_quoteflag))))
		return (NULL);
	return (f);
}

void		ft_ini_quoteflag(t_quoteflag *f)
{
	f->i = -1;
	f->start = -1;
	f->end = -1;
	f->br_count = 0;
	f->br_flag = 0;
	f->qflag = 0;
	f->b_sl = 0;
	f->rc = 0;
	f->subs_start = -1;
}

char		**ft_test_calc(t_quoteflag *f, char **str)
{
	f->rc = 0;
	if (f->qflag == 0 && ((f->br_flag == 1 && str[f->n][f->i] == ')') ||
	(f->br_flag == 2 && str[f->n][f->i] == '}')))
	{
		f->br_count--;
		if (f->br_count == 0)
		{
			f->br_flag = 0;
			if (f->start != -1 && str[f->n][f->start + 1] == '(' &&
			((f->end = f->i))
			&& ft_check_ekran(str[f->n], f->start - 1) < 2)
			{
				str = ft_tst_calc(str, f->n, f->start, f->end);
				if (g_calc != 0 && ((f->rc = 1)))
					return (str);
				f->i = -1;
				f->rc = 2;
			}
		}
	}
	return (str);
}
