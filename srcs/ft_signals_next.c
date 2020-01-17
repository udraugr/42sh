/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 22:44:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_dfl(void)
{
	signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
}

void	ft_test_cmd_list(pid_t pid, int status)
{
	t_cmdlist	*cur_cmd;

	if ((g_job == 0 || g_subst > 0) && g_pipe &&
	((cur_cmd = g_pipe->first_cmd)))
	{
		while (cur_cmd)
		{
			if ((cur_cmd->pid_z != 0) && (cur_cmd->pid_z == pid))
			{
				if (!(cur_cmd->next))
					ft_set_cmd_exit_status(status);
				cur_cmd->pid = 0;
				cur_cmd->status = status;
			}
			cur_cmd = cur_cmd->next;
		}
	}
}

int		ft_test_sig_list(int signo)
{
	if (signo == SIGCHLD || signo == SIGINT || signo == SIGTTIN
		|| signo == SIGTTOU || signo == SIGTSTP || signo == SIGQUIT)
		return (1);
	return (0);
}

int		ft_job_stopped(t_job *j)
{
	t_proc	*p;
	int		i;

	p = j->first_proc;
	while (p)
	{
		if ((i = kill(p->pid, 0)) == 0)
			p->completed = 1;
		if ((p->completed != 1) && (p->stopped != 1))
			return (0);
		p = p->next;
	}
	j->stat_job = ft_strcpy(j->stat_job, "Done                     ");
	j->ready = 1;
	return (1);
}

int		ft_job_completed(t_job *j)
{
	t_proc	*p;
	int		i;

	p = j->first_proc;
	while (p)
	{
		if ((i = kill(p->pid, 0)) == 0)
			p->completed = 1;
		if ((p->completed != 1))
			return (0);
		p = p->next;
	}
	j->stat_job = ft_strcpy(j->stat_job, "Done                     ");
	j->ready = 1;
	return (1);
}
