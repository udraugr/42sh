/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/16 21:41:34 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert_job(t_job *cur_job)
{
	t_job	*tmp;

	tmp = g_job_first;
	while (tmp)
	{
		if (tmp == g_job_first && tmp->num > 1 && ((cur_job->num = 1)))
		{
			cur_job->next = tmp;
			g_job_first = cur_job;
			return ;
		}
		else if (tmp->next && tmp->num + 1 < tmp->next->num)
		{
			cur_job->num = tmp->num + 1;
			cur_job->next = tmp->next;
			tmp->next = cur_job;
			return ;
		}
		else if (!(tmp->next) && tmp != cur_job && ((tmp->next = cur_job)))
		{
			cur_job->num = tmp->num + 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_free_job(t_job *del)
{
	if (del->orig_cmd)
		free(del->orig_cmd);
	if (del->first_proc)
		ft_del_proc_list(del->first_proc);
	if (del->stat_job)
		free(del->stat_job);
	free(del);
}

t_job	*ft_del_job(t_job *del)
{
	t_job	*prev;
	t_job	*tmp;

	tmp = g_job_first;
	prev = NULL;
	while (tmp && del)
	{
		if (tmp == del)
		{
			if (prev)
				prev->next = del->next;
			else
			{
				g_job_first = del->next;
				prev = g_job_first;
			}
			ft_free_job(del);
			break ;
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
	ft_set_job_plus();
	return (prev);
}

t_job	*ft_new_job(t_cmdlist *cur_cmd)
{
	t_job	*cur_job;

	cur_job = malloc(sizeof(t_job));
	cur_job->stat_job = ft_strdup("Running               ");
	cur_job->ind = g_job_ind;
	g_job_ind++;
	cur_job->next = NULL;
	cur_job->first_proc = NULL;
	cur_job->orig_cmd = NULL;
	cur_job->pgid = cur_cmd->pid_z;
	cur_job->ready = 0;
	return (cur_job);
}

int		ft_if_job(t_cmdlist *cur_cmd)
{
	t_job	*cur_job;

	cur_job = NULL;
	if (g_job == 1 && g_subst == 0)
	{
		if (cur_cmd->nr == 1)
		{
			cur_job = ft_new_job(cur_cmd);
			if (!(g_job_first))
			{
				g_job_first = cur_job;
				cur_job->num = 1;
			}
			else
				ft_insert_job(cur_job);
			cur_job->orig_cmd = ft_strncpy(ft_strnew((size_t)
			(g_job_end + 1)), g_job_start, g_job_end);
			ft_set_job_plus();
			ft_print_start_job(cur_job);
		}
		ft_add_proc(cur_cmd, cur_job);
	}
	return (1);
}
