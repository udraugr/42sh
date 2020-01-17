/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntrl_subst2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:42:51 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 15:02:49 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_resize_matr(char **str)
{
	int n;
	int add;

	n = -1;
	add = 0;
	while (str && str[++n])
	{
		if ((add = ft_split_pipes_words(str[n])) > 1)
		{
			str = ft_resize_matr_n(str, n, add);
			n--;
			add = 0;
		}
	}
	return (str);
}

char		**ft_resize_matr_n(char **str, int n, int add)
{
	int		i;
	char	**ret;
	char	**tmp;
	int		j;

	i = ft_calc_matr_rows(str);
	ret = str;
	tmp = ft_split_pipes(str[n]);
	free(str[n]);
	ret = (char **)malloc(sizeof(char *) * (i + add));
	ret[i + add - 1] = NULL;
	j = -1;
	while (++j < i + add - 1)
	{
		if (j < n)
			ret[j] = str[j];
		else if (j >= n && j <= n + add - 1)
			ret[j] = tmp[j - n];
		else
			ret[j] = str[j - add + 1];
	}
	free(str);
	free(tmp);
	return (ret);
}

void		ft_subst_tst_ps(t_quoteflag *f, char **str, int n)
{
	if (f->qflag != 2 && str[n][f->i] == '\\' && ((f->b_sl = f->b_sl + 1)))
		f->b_sl = f->b_sl % 2;
	if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 1) &&
	str[n][f->i] == '(' && f->b_sl == 0)
	{
		f->br_flag = 1;
		f->br_count++;
	}
	else if (f->qflag == 0 && f->br_flag == 1 && str[n][f->i] == '(')
		f->br_count++;
	else if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 2) &&
	str[n][f->i] == '{' && f->b_sl == 0)
	{
		f->br_flag = 2;
		f->br_count++;
	}
	else if (f->qflag == 0 && f->br_flag == 2 && str[n][f->i] == '{' &&
			f->b_sl == 0)
		f->br_count++;
}

void		ft_subst_tst_pf(t_quoteflag *f, char **str, int n)
{
	if ((f->qflag == 2 && f->b_sl == 0 && str[n][f->i] == '\'' &&
	(f->i == 0 || str[n][f->i - 1] != '\\')))
		f->qflag = 0;
	else if (f->qflag == 0 && f->b_sl == 0 && str[n][f->i] == '\'')
		f->qflag = 2;
	if (f->qflag == 0 && f->br_flag == 0 && f->b_sl == 0
	&& str[n][f->i] == '$' && str[n][f->i + 1] && str[n][f->i + 1] == '(')
		f->start = f->i + 1;
	if (f->qflag == 0 && str[n][f->i] != '\\' && f->b_sl == 1)
		f->b_sl = 0;
}

int			ft_subst_tst_exe(t_quoteflag *f, char **str, int n)
{
	if (f->qflag == 0 && f->b_sl == 0 && ((f->br_flag == 1 &&
	str[n][f->i] == ')') || (f->br_flag == 2 && str[n][f->i] == '}')))
	{
		f->br_count--;
		if (f->br_count == 0)
		{
			f->br_flag = 0;
			if (f->start != -1 && str[n][f->start + 1] != '(' &&
			((f->end = f->i)))
			{
				str = ft_cnt_subs_exe(str, n, f->start, f->end);
				if (f->start + 1 != f->end)
					f->i = -1;
				return (1);
			}
		}
	}
	return (0);
}
