/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:17:45 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 13:03:11 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parse_if_3(t_quoteflag *f, char *str)
{
	char	*av;

	if (f->i == 0 && ft_test_args(str + f->i_cmd) == 0)
		return (ft_free_qf(f));
	if (f->i == 0 && g_subst == 0 &&
			((g_job = ft_test_job(str, f->i_cmd))) && g_and_or_line)
	{
		av = ft_get_shell_str(g_job_start, g_job_end);
		if (ft_parse_cmd(av, ft_strlen(av)) == 1)
		{
			free(av);
			return (ft_free_qf(f));
		}
		free(av);
		if (g_sub_str && g_shell_num != 0)
			return (ft_free_qf(f));
		f->i_cmd = (g_job_start - str) + g_job_end + 1;
		g_job_start = NULL;
		g_job_end = 0;
		g_job = 0;
		f->i = -1;
	}
	else
		return (2);
	return (0);
}

int		ft_parse_if_2(t_quoteflag *f, char *str)
{
	if (f->b_sl != 0)
		return (2);
	if (f->qflag == 0 && str[f->i + f->i_cmd] == '"')
		f->qflag = 1;
	else if (f->qflag == 0 && str[f->i + f->i_cmd] == '\'')
		f->qflag = 2;
	else if ((f->qflag == 0 && str[f->i + f->i_cmd] == '(' && ((f->qflag = 3)))
	|| (f->qflag == 0 && str[f->i + f->i_cmd] == '{' && ((f->qflag = 4))))
		f->br_count++;
	else if ((f->qflag == 3 && str[f->i + f->i_cmd] == '(') ||
			(f->qflag == 4 && str[f->i + f->i_cmd] == '{'))
		f->br_count++;
	else if ((f->qflag == 3 && str[f->i + f->i_cmd] == ')') ||
		(f->qflag == 4 && str[f->i + f->i_cmd] == '}'))
	{
		f->br_count--;
		if (f->br_count == 0)
			f->qflag = 0;
	}
	else
		return (2);
	return (0);
}

int		ft_parse_if_1(t_quoteflag *f, char *str)
{
	if (f->b_sl != 0)
		return (2);
	if (f->qflag == 0 && (str[f->i + f->i_cmd] == ')' ||
	str[f->i + f->i_cmd] == '}') && f->br_count <= 0 &&
	ft_print_msg(": parse error: ", str + f->i_cmd + f->i) == -1)
		return (ft_free_qf(f));
	else if ((f->qflag == 1 && str[f->i + f->i_cmd] == '"') ||
		(f->qflag == 2 && str[f->i + f->i_cmd] == '\''))
		f->qflag = 0;
	else if (f->qflag == 0 && (str[f->i + f->i_cmd] == ';' ||
	(g_job = ft_ampers_test(str, f->i, f->i_cmd)) == 1))
	{
		if (ft_check_pipe_n(str, f))
			return (1);
		if (ft_parse_cmd(str + f->i_cmd, f->i) == 1)
			return (ft_free_qf(f));
		if (g_sub_str && g_shell_num != 0)
			return (ft_free_qf(f));
		f->i_cmd = f->i_cmd + f->i + 1;
		f->i = -1;
	}
	else
		return (2);
	return (0);
}

int		ft_parse_if_0(t_quoteflag *f, char *str)
{
	if (f->b_sl != 0)
		return (0);
	if (f->qflag == 0 && ft_strncmp(str + f->i + f->i_cmd, "&&", 2) == 0
	&& (f->i + f->i_cmd == 0 || str[f->i + f->i_cmd - 1] != '\\'))
	{
		if (ft_test_f_andor(f, str) || ft_check_pipe_n(str, f))
			return (1);
		if (ft_parse_cmd(str + f->i_cmd, f->i) == 1)
			g_skip = 1;
		if (g_sub_str && g_shell_num != 0)
			return (ft_free_qf(f));
		ft_set_andor(1, f);
	}
	else if (f->qflag == 0 && ft_strncmp(str + f->i + f->i_cmd, "||", 2) == 0
	&& (f->i + f->i_cmd == 0 || str[f->i + f->i_cmd - 1] != '\\'))
	{
		if (ft_test_f_andor(f, str) || ft_check_pipe_n(str, f))
			return (1);
		if (ft_parse_cmd(str + f->i_cmd, f->i) == 1)
			g_skip = 1;
		if (g_sub_str && g_shell_num != 0)
			return (ft_free_qf(f));
		ft_set_andor(2, f);
	}
	return (0);
}

void	ft_parse_line(char *str)
{
	t_quoteflag	*f;
	int			rc;

	f = ft_init_parse_init();
	while (str && str[++f->i + f->i_cmd] && ((rc = 0) == 0))
	{
		if ((rc = ft_parse_if_4(str, f)) != -777 && rc == 1)
			return ;
		else if (rc == 2)
		{
			if (ft_parse_if_2(f, str) == 2)
			{
				rc = ft_parse_if_1(f, str);
				if (rc == 1)
					return ;
				else if (rc == 2 && (ft_parse_if_0(f, str) == 1))
					return ;
			}
			if (f->b_sl == 1 && str[f->i + f->i_cmd] != '\\')
				f->b_sl = 0;
		}
	}
	ft_parse_cmd(str + f->i_cmd, f->i);
	g_job = -1;
	ft_free_qf(f);
}
