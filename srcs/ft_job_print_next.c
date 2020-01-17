/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/10 20:43:47 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_jobs(void)
{
	t_job	*job;

	job = g_job_first;
	while (job)
	{
		if (job->ready > 0)
		{
			ft_print_job_line(job, 0);
			if (job->ready == 1 || job->ready == 4)
				job = ft_del_job(job);
			else
				job->ready = 0;
		}
		else
			job = job->next;
	}
}

int		ft_jobs_usage(char *av)
{
	ft_set_shell("?", "1");
	ft_print_msg(": jobs: invalid option: ", av);
	ft_print_msg(": usage: jobs [-l] [jobspec ...]", " ");
	return (1);
}

int		ft_cmd_jobs(char **av)
{
	int		i;
	char	*tmp;
	int		fl;
	int		start;

	ft_set_shell("?", "0");
	i = 1;
	fl = 0;
	tmp = NULL;
	start = 0;
	while (av && av[i] && start == 0)
	{
		if (start == 0 && av[i][0] == '-' && ft_strchr(av[i], 'l'))
			fl = 1;
		else if (start == 0 && av[i][0] == '-')
			return (ft_jobs_usage(av[i]));
		else
			start = i;
		i++;
	}
	ft_print_job_list(i - 1, start, fl, av);
	return (1);
}

void	ft_print_job_info(t_job *job, t_job *jobdel, int fl)
{
	while (job)
	{
		ft_print_job_line(job, fl);
		if (job->ready == 1 || job->ready == 4)
		{
			jobdel = job->next;
			job = ft_del_job(job);
			job = jobdel;
		}
		else
		{
			job->ready = 0;
			job = job->next;
		}
	}
}

void	ft_print_job_list(int i, int start, int fl, char **av)
{
	t_job	*job;
	t_job	*jobdel;

	job = g_job_first;
	jobdel = NULL;
	if (i == 0 || start == 0)
		ft_print_job_info(job, jobdel, fl);
	else
	{
		while (av[start])
		{
			ft_print_if_job(av[start], fl);
			start++;
		}
	}
}
