/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_shell_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 14:43:24 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_cmd_list_ini(t_pipe *p_head, int flpi)
{
	g_pipe = p_head;
	g_flpi = flpi;
	p_head->cur_cmd = p_head->first_cmd;
	p_head->cur_cmd->avcmd = ft_isnot(p_head->cur_cmd->avcmd);
	if (g_parent_pid == getpid())
		g_pgid = 0;
}

void	ft_set_pgid(t_cmdlist *cmd, int flpi)
{
	if ((g_job == 1) || flpi != -777)
	{
		if (g_pgid == 0)
		{
			g_pgid = cmd->pid;
			if (g_job == 0 || ft_child_check_subsh(cmd))
				g_pgid = getpid();
		}
		setpgid(cmd->pid, g_pgid);
		if (g_job == 0 || ft_child_check_subsh(cmd))
			tcsetpgrp(0, g_pgid);
	}
}

int		ft_do_cmd_loop(t_pipe *p_head, int fd0[2], int fd1[2], int flpi)
{
	if (g_job == 1 && g_sub_str)
		g_job = 0;
	while (p_head->cur_cmd && (g_nopipe_start = 1))
	{
		if ((ft_get_heretext(p_head->cur_cmd) == -1) ||
		(flpi > 0 && ((ft_set_fd_pipes(p_head, fd0, fd1) == -1))) ||
		(flpi < 1 && g_job != 1 && (fd_set_nopipe(p_head) == -1)))
			return (-1);
		if (ft_fork(p_head) == -1)
			return (-1);
		else if (p_head->cur_cmd->pid == 0)
		{
			ft_child_pipe_exec(p_head->cur_cmd, flpi);
			if (g_sub_str && g_subshell > 0)
				return (-1);
		}
		else if (p_head->cur_cmd->pid > 0)
		{
			ft_parent_pipe_next(p_head->cur_cmd, fd0, fd1, flpi);
			p_head->cur_cmd = p_head->cur_cmd->next;
		}
	}
	return (0);
}
