/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 13:50:47 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_split_words_p4(t_quoteflag *f, char *str, int *wcount)
{
	if (f->qflag == 0 && f->br_flag == 0 && str[f->i] == '|' &&
	(f->i == 0 || f->b_sl == 0))
		(*wcount)++;
	else if (f->qflag == 0 && f->br_flag == 0 && ft_isspace(str[f->i]) == 0 &&
	(f->i == 0 || (ft_isspace(str[f->i - 1]) == 1 &&
	!ft_check_ekran(str, f->i - 1))
	|| (ft_strchr("|)}", str[f->i - 1]) && !ft_check_ekran(str, f->i - 1)))
	&& (f->subs_end == -1 || f->subs_end != f->i - 1))
		(*wcount)++;
	if ((f->qflag == 1 && str[f->i] == '"' && f->b_sl == 0) ||
	(f->qflag == 2 && str[f->i] == '\'' && f->b_sl == 0))
		f->qflag = 0;
	else if (f->qflag == 0 && str[f->i] == '"' && (f->i == 0 || f->b_sl == 0))
		f->qflag = 1;
	else if (f->qflag == 0 && str[f->i] == '\'' && (f->i == 0 || f->b_sl == 0))
		f->qflag = 2;
	else if (f->qflag != 2 && str[f->i] != '\\' && f->b_sl == 1)
		f->b_sl = 0;
	f->i++;
}

int			ft_split_words_p3(t_quoteflag *f, char *str, int *wcount)
{
	if (f->qflag == 0 && ((f->br_flag == 1 && str[f->i] == ')') ||
	(f->br_flag == 2 && str[f->i] == '}')) && f->b_sl == 0)
	{
		f->br_count--;
		if (f->br_count == 0)
		{
			f->br_flag = 0;
			if (f->flsub == 1)
			{
				f->flsub = 0;
				f->subs_end = f->i;
			}
			else
				(*wcount)++;
			f->i++;
			return (1);
		}
	}
	return (0);
}

void		ft_split_words_p2(t_quoteflag *f, char *str)
{
	if (f->qflag == 0 && f->br_flag == 1 && str[f->i] == '(' &&
	f->b_sl == 0)
		f->br_count++;
	else if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 2) &&
	str[f->i] == '{' && f->b_sl == 0 &&
	(f->i == 0 || ft_strchr(" ;|&", str[f->i - 1])))
	{
		f->br_flag = 2;
		f->br_count++;
	}
	else if (f->qflag == 0 && f->br_flag == 2 && str[f->i] == '{' &&
	f->b_sl == 0)
		f->br_count++;
}

void		ft_split_words_p1(t_quoteflag *f, char *str)
{
	if (f->qflag != 2 && str[f->i] == '\\' && ((f->b_sl = f->b_sl + 1)))
		f->b_sl = f->b_sl % 2;
	if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 1) &&
	str[f->i] == '(' && f->b_sl == 0 &&
	(f->i == 0 || ft_strchr(" ;|&$", str[f->i - 1])))
	{
		f->br_flag = 1;
		f->br_count++;
		if (f->br_count == 1 && f->i > 0 && str[f->i - 1] == '$' &&
		(f->i - 1 == 0 || f->b_sl == 0) && (f->flsub = 1))
			f->subs_start = f->i - 1;
	}
	else if (f->qflag == 0 && (f->br_flag == 0 || f->br_flag == 2) &&
	str[f->i] == '{' && f->b_sl == 0
	&& (f->i == 0 || ft_strchr(" ;|&$", str[f->i - 1])))
	{
		f->br_flag = 2;
		f->br_count++;
		if (f->br_count == 1 && f->i > 0 && str[f->i - 1] == '$' &&
		(f->i - 1 == 0 || f->b_sl == 0) && (f->flsub = 1))
			f->subs_start = f->i - 1;
	}
	else
		ft_split_words_p2(f, str);
}

int			ft_split_pipes_words77(char *str)
{
	t_quoteflag	*f;
	int			wcount;

	f = ft_get_quoteflag();
	ft_ini_quoteflag_spl(f);
	wcount = 0;
	while (str && str[f->i])
	{
		if (f->qflag == 0 && f->br_flag == 0 && str[f->i] == ')' && f->b_sl == 0
		&& f->i > 0 && f->flsub == 0 && ft_strlen(str) >
		(size_t)(f->i_cmd + f->i + 1) &&
		ft_get_nextp_world(str + f->i + 1) == '(')
			return (1 + ft_pr_msg_rc(" : parse error in command ", str + f->i));
		ft_split_words_p1(f, str);
		if (ft_split_words_p3(f, str, &wcount) == 1)
			continue;
		ft_split_words_p4(f, str, &wcount);
	}
	if (f->br_count > 0)
	{
		ft_print_msg(" : parse error : ", str);
		wcount = 0;
	}
	free(f);
	return (wcount);
}
