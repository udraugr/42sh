/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words_cut2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 23:38:21 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_all_words4s(t_pipeflag *fl, char const *str)
{
	if (fl->qflag == 0 && fl->br_flag == 1 && str[fl->i] == '('
	&& fl->b_sl == 0)
		fl->br_count++;
	else if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 2) && str
	[fl->i] == '{' && fl->b_sl == 0 &&
	(fl->i == 0 || ft_strchr(" ;|&", str[fl->i - 1])))
	{
		fl->br_flag = 2;
		fl->br_count++;
		if (fl->br_count == 1)
			fl->start = fl->i;
	}
	else if (fl->qflag == 0 && fl->br_flag == 2 && str[fl->i] == '{'
	&& fl->b_sl == 0)
		fl->br_count++;
}

void	ft_all_words3s(t_pipeflag *fl, char const *str)
{
	if (fl->qflag == 0 && fl->br_flag == 0 && str[fl->i] == '|' &&
	(fl->i == 0 || fl->b_sl == 0))
		ft_pipe_split_3s(fl, str);
	else if (fl->qflag == 0 && fl->br_flag == 0 && fl->flag == 1 &&
	ft_isspace(str[fl->i]) == 1 && !ft_check_ekran((char *)str, fl->i)
	&& fl->i > 0 && ft_isspace(str[fl->i - 1]) == 0)
		ft_pipe_split_4s(fl, str);
	else
		ft_pipe_split_6(fl, str);
	if ((fl->qflag == 1 && str[fl->i] == '"' && fl->b_sl == 0) ||
		(fl->qflag == 2 && str[fl->i] == '\'' && fl->b_sl == 0))
		fl->qflag = 0;
	else if (fl->qflag == 0 && str[fl->i] == '"' &&
	(fl->i == 0 || fl->b_sl == 0))
		fl->qflag = 1;
	else if (fl->qflag == 0 && str[fl->i] == '\'' &&
	(fl->i == 0 || fl->b_sl == 0))
		fl->qflag = 2;
	else if (fl->qflag != 2 && str[fl->i] != '\\' && fl->b_sl == 1)
		fl->b_sl = 0;
}

int		ft_all_words2s(t_pipeflag *fl, char const *str)
{
	if (fl->qflag == 0 && ((fl->br_flag == 1 && str[fl->i] == ')') ||
	(fl->br_flag == 2 && str[fl->i] == '}'))
	&& fl->b_sl == 0)
	{
		fl->br_count--;
		if (fl->br_count == 0)
		{
			fl->br_flag = 0;
			if (fl->flsub == 1)
				fl->flsub = 0;
			else
			{
				fl->i++;
				ft_pipe_split_4s(fl, str);
				fl->i--;
			}
			return (1);
		}
	}
	return (0);
}

void	ft_all_words1s(t_pipeflag *fl, char const *str)
{
	if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 1) &&
	str[fl->i] == '(' && fl->b_sl == 0 && (fl->i == 0 ||
	ft_strchr(" ;|&$", str[fl->i - 1])) && (fl->br_flag = 1))
	{
		fl->br_count++;
		if (fl->br_count == 1 && fl->i > 0 && str[fl->i - 1] == '$' &&
		(fl->i - 1 == 0 || fl->b_sl == 0))
			fl->flsub = 1;
		else if (fl->br_count == 1 && fl->flsub == 0)
			ft_pipe_split_sps(fl, str);
	}
	else if (fl->qflag == 0 && (fl->br_flag == 0 || fl->br_flag == 2) &&
	str[fl->i] == '{' && fl->b_sl == 0
	&& (fl->i == 0 || ft_strchr(" ;|&$", str[fl->i - 1])))
	{
		fl->br_flag = 2;
		fl->br_count++;
		if (fl->br_count == 1 && fl->i > 0 && str[fl->i - 1] == '$' &&
		(fl->i - 1 == 0 || fl->b_sl == 0))
			fl->flsub = 1;
		else if (fl->br_count == 1 && fl->flsub == 0)
			ft_pipe_split_sps(fl, str);
	}
	else
		ft_all_words4s(fl, str);
}

int		ft_split_pipes_words(char *str)
{
	t_pipeflag	*fl;
	int			wcount;

	fl = ft_pipe_split_ini();
	while (++fl->i < (int)ft_strlen(str) && (str[fl->i]))
	{
		if (fl->qflag != 2 && str[fl->i] == '\\' && ((fl->b_sl = fl->b_sl + 1)))
			fl->b_sl = fl->b_sl % 2;
		ft_all_words1s(fl, str);
		if (ft_all_words2s(fl, str) == 1)
			continue ;
		ft_all_words3s(fl, str);
	}
	if (fl->flag == 1)
	{
		ft_get_words();
		fl->count++;
	}
	wcount = fl->count;
	free(fl);
	return (wcount);
}
