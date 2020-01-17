/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 19:03:56 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_test_job_pf(char *str, int start, t_quoteflag *f)
{
	if ((f->qflag == 3 && str[f->i + start] == '(') ||
			(f->qflag == 4 && str[f->i + start] == '{'))
		f->br_count++;
	else if ((f->qflag == 3 && str[f->i + start] == ')') ||
			(f->qflag == 4 && str[f->i + start] == '}'))
	{
		f->br_count--;
		if (f->br_count == 0)
			f->qflag = 0;
	}
	else if (f->qflag == 0 && ((ft_strncmp(str + f->i + start, "&&", 2) == 0)
	|| (ft_strncmp(str + f->i + start, "||", 2) == 0)) &&
	(f->i + start == 0 || str[f->i + start - 1] != '\\'))
		g_and_or_line = 1;
}

int			ft_test_job_ps(char *str, int start, t_quoteflag *f)
{
	int	rc;

	rc = 0;
	if (f->qflag == 0 && str[f->i + start] == '"')
		f->qflag = 1;
	else if ((f->qflag == 1 && str[f->i + start] == '"') ||
		(f->qflag == 2 && str[f->i] == '\''))
		f->qflag = 0;
	else if (f->qflag == 0 && str[f->i + start] == '\'')
		f->qflag = 2;
	else if ((f->qflag == 0 && str[f->i + start] == '(' && ((f->qflag = 3))) ||
			(f->qflag == 0 && str[f->i + start] == '{' && ((f->qflag = 4))))
		f->br_count++;
	else
		rc = 1;
	return (rc);
}

int			ft_test_job(char *str, int start)
{
	t_quoteflag	*f;
	int			i;

	f = ft_get_quoteflag();
	ft_ini_quoteflag(f);
	while (str && str[++f->i + start])
	{
		if (ft_test_job_ps(str, start, f) == 1)
			ft_test_job_pf(str, start, f);
		if (f->qflag == 0 && (str[f->i + start] == ';'))
		{
			free(f);
			return (0);
		}
		if (f->qflag == 0 && ft_ampers_test(str, f->i, start) == 1)
		{
			i = f->i;
			free(f);
			return (ft_set_job_str(str + start, i));
		}
	}
	free(f);
	return (0);
}
