/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/17 12:49:57 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_num_to_str(int i)
{
	char	*num;

	num = ft_strnew(20);
	num[0] = '\0';
	num = ft_putfnbr(i, num);
	return (num);
}

char	*ft_print_job_pref(t_job *cur_job)
{
	char	*tmp;
	char	*num;
	int		i;

	tmp = NULL;
	if ((tmp = ft_strdup("")))
	{
		tmp = ft_strfjoin(tmp, "[");
		num = ft_num_to_str(cur_job->num);
		tmp = ft_strfjoin(tmp, num);
		free(num);
		tmp = ft_strfjoin(tmp, "]");
		i = ft_strlen(tmp);
		tmp = ft_strfjoin(tmp, " ");
		ft_strncpy(tmp + i, &cur_job->flag, 1);
		tmp = ft_strfjoin(tmp, " ");
	}
	return (tmp);
}

void	ft_print_start_job(t_job *cur_job)
{
	char	*tmp;
	char	*num;

	if (g_subshell == 0 && (tmp = ft_print_job_pref(cur_job)))
	{
		num = ft_num_to_str(cur_job->pgid);
		tmp = ft_strfjoin(tmp, num);
		free(num);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}

void	ft_job_ind_plus(t_job *job, int *last, int *prev)
{
	while (job)
	{
		if (job->ind > *last)
		{
			*prev = *last;
			*last = job->ind;
		}
		else if (job->ind > *prev)
			*prev = job->ind;
		job->flag = ' ';
		job = job->next;
	}
}

void	ft_set_job_plus(void)
{
	int		last;
	int		prev;
	t_job	*job;

	last = 0;
	prev = 0;
	job = g_job_first;
	ft_job_ind_plus(job, &last, &prev);
	job = g_job_first;
	while (job)
	{
		if (job->ind == last)
			job->flag = '+';
		else if (job->ind == prev)
			job->flag = '-';
		job = job->next;
	}
}
