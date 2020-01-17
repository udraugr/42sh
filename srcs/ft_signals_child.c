/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 19:29:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_set(void)
{
	signal(SIGCHLD, ft_signal_handler_rl);
	signal(SIGINT, ft_signal_handler_rl);
	signal(SIGTTIN, ft_signal_handler_rl);
	signal(SIGTTOU, ft_signal_handler_rl);
	signal(SIGTSTP, ft_signal_handler_rl);
	signal(SIGQUIT, ft_signal_handler_rl);
	signal(SIGCONT, ft_signal_handler_rl);
}

void	ft_print_sig(pid_t pid, int signo, int status)
{
	char	*tmp;

	tmp = ft_strdup("pid = ");
	if (pid)
		tmp = ft_add_strnum(tmp, pid);
	else
		tmp = ft_add_strnum(tmp, getpid());
	if (signo && (tmp = ft_strfjoin(tmp, " signo = ")))
		tmp = ft_add_strnum(tmp, signo);
	if (status)
	{
		if (WIFSTOPPED(status))
		{
			tmp = ft_strfjoin(tmp, " stopped by =");
			tmp = ft_add_strnum(tmp, WSTOPSIG(status));
		}
		else if (WIFSIGNALED(status))
		{
			tmp = ft_strfjoin(tmp, " finished by =");
			tmp = ft_add_strnum(tmp, WTERMSIG(status));
		}
	}
	if (g_signal == 1)
		ft_print_msg(" : Info signal: ", tmp);
	free(tmp);
}

void	ft_sig_do(int signo, int status, pid_t pid)
{
	if (signo == SIGCHLD && pid > 0)
	{
		ft_print_sig(pid, signo, status);
		if (WIFSTOPPED(status))
		{
			if (g_parent_pid == getpid())
			{
				if (WSTOPSIG(status) == 18)
					ft_test_tstp(pid, status);
				tcsetpgrp(0, getpid());
			}
			else
			{
				if (WSTOPSIG(status) == 18)
					kill(g_parent_pid, SIGTSTP);
			}
		}
		ft_test_job_status(pid, status);
		ft_test_cmd_list(pid, status);
	}
	if (signo == SIGTSTP && g_parent_pid == getpid())
	{
		ft_test_tstp(pid, status);
		tcsetpgrp(0, getpid());
	}
}
