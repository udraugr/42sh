/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_job_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 20:50:28 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_one_line(t_proc *proc, t_job *job, int *len)
{
	char	*num;
	char	*tmp;

	if (proc == job->first_proc)
	{
		if ((tmp = ft_print_job_pref(job)))
			*len = ft_strlen(tmp);
	}
	else
	{
		tmp = ft_strdup("                ");
		tmp[*len] = '\0';
	}
	num = ft_num_to_str(proc->pid);
	tmp = ft_strfjoin(tmp, num);
	free(num);
	tmp = ft_strfjoin(tmp, " ");
	if (proc == job->first_proc)
		tmp = ft_strfjoin(tmp, job->stat_job);
	else
		tmp = ft_strfjoin(tmp, "                    ");
	tmp = ft_strfjoin(tmp, proc->argv[0]);
	tmp = ft_strfjoin(tmp, "\n");
	ft_putstr(tmp);
	free(tmp);
}

void	ft_print_job_line(t_job *job, int fl)
{
	char	*tmp;
	int		len;
	t_proc	*proc;

	len = 0;
	if (fl == 1)
	{
		proc = job->first_proc;
		while (proc)
		{
			ft_print_one_line(proc, job, &len);
			proc = proc->next;
		}
	}
	else
	{
		if ((tmp = ft_print_job_pref(job)))
		{
			tmp = ft_strfjoin(tmp, job->stat_job);
			tmp = ft_strfjoin(tmp, job->orig_cmd);
			tmp = ft_strfjoin(tmp, "\n");
			ft_putstr(tmp);
			free(tmp);
		}
	}
}

void	ft_print_if_job(char *str, int fl)
{
	t_job	*job;

	job = g_job_first;
	while (job)
	{
		if (job->num == ft_atoi(str))
		{
			ft_print_job_line(job, fl);
			job->ready = 0;
			return ;
		}
		job = job->next;
	}
}
