/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words_cut.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 20:45:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_all_words4(t_pipeflag *fl, char const *str)
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

void	ft_all_words3(t_pipeflag *fl, char const *str, char **ret)
{
	if (fl->qflag == 0 && fl->br_flag == 0 && str[fl->i] == '|' &&
	(fl->i == 0 || fl->b_sl == 0))
		ft_pipe_split_3(fl, ret, str);
	else if (fl->qflag == 0 && fl->br_flag == 0 && fl->flag == 1 &&
	ft_isspace(str[fl->i]) == 1 && !ft_check_ekran((char *)str, fl->i)
	&& fl->i > 0 && ft_isspace(str[fl->i - 1]) == 0)
		ft_pipe_split_4(fl, ret, str);
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

int		ft_all_words2(t_pipeflag *fl, char const *str, char **ret)
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
				ft_pipe_split_4(fl, ret, str);
				fl->i--;
			}
			return (1);
		}
	}
	return (0);
}

void	ft_all_words1(t_pipeflag *fl, char const *str, char **ret)
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
			ft_pipe_split_sp(fl, ret, str);
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
			ft_pipe_split_sp(fl, ret, str);
	}
	else
		ft_all_words4(fl, str);
}

int		ft_all_pipe_words(char **ret, char const *str)
{
	t_pipeflag	*fl;

	fl = ft_pipe_split_ini();
	while (++fl->i < (int)ft_strlen(str) && (str[fl->i]))
	{
		if (fl->qflag != 2 && str[fl->i] == '\\' && ((fl->b_sl = fl->b_sl + 1)))
			fl->b_sl = fl->b_sl % 2;
		ft_all_words1(fl, str, ret);
		if (ft_all_words2(fl, str, ret) == 1)
			continue ;
		ft_all_words3(fl, str, ret);
	}
	if (fl->flag == 1)
		ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
	free(fl);
	ret = ft_press_matr(ret);
	return (0);
}
