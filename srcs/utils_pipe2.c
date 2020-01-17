/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/18 12:04:24 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parent_close_pipe(int code, int fd0[2], int fd1[2])
{
	if (code == 0)
	{
		if (fd0[0] != -1)
			close(fd0[0]);
		if (fd0[1] != -1)
			close(fd0[1]);
		ft_init_arr_fd(0, fd0, fd1);
	}
	else
	{
		if (fd1[0] != -1)
			close(fd1[0]);
		if (fd1[1] != -1)
			close(fd1[1]);
		ft_init_arr_fd(1, fd0, fd1);
	}
}

void	ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
		int fd1[2], int flpi)
{
	ft_set_pgid(cur_cmd, flpi);
	ft_if_job(cur_cmd);
	if (flpi > 0 && cur_cmd->nr == 1)
		return ;
	if (flpi > 0 && cur_cmd->nr % 2 == 1)
		ft_parent_close_pipe(0, fd0, fd1);
	else if (flpi > 0 && cur_cmd->nr % 2 != 1)
		ft_parent_close_pipe(1, fd0, fd1);
}

void	ft_pipe_wait_fin_loop(int *q, t_cmdlist *cur_cmd)
{
	int			status;
	int			r;
	int			j;

	r = 0;
	while (cur_cmd)
	{
		if (cur_cmd->pid != 0)
		{
			(*q)++;
			status = 0;
			if ((j = waitpid(cur_cmd->pid, &status,
							WNOHANG | WUNTRACED)) == cur_cmd->pid)
			{
				r = r + ft_get_cmd_exit_status(status);
				if (!(cur_cmd->next))
					(r != 0) ? ft_set_shell("?", "1") : ft_set_shell("?", "0");
				cur_cmd->pid = 0;
			}
		}
		cur_cmd = cur_cmd->next;
	}
}

void	ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd, t_cmdlist *first_cmd,
		t_cmdlist *last_cmd, int flpi)
{
	int			q;

	if ((g_job == 0 || g_subshell) && flpi > 0)
	{
		while (1)
		{
			cur_cmd = first_cmd;
			q = 0;
			ft_pipe_wait_fin_loop(&q, cur_cmd);
			if (q == 0)
			{
				(void)last_cmd;
				if (flpi == 0)
					first_cmd = ft_redir_io_restore(first_cmd);
				return ;
			}
		}
	}
	else
		first_cmd = ft_redir_io_restore(first_cmd);
}

void	ft_child_pipe_varset(t_cmdlist *cur_cmd)
{
	ft_close_g_semafors();
	g_semafor = cur_cmd->semafor;
	g_bsemafor = cur_cmd->bsemafor;
	g_sem_name = cur_cmd->sem_name;
	g_bsem_name = cur_cmd->bsem_name;
	g_sem_fl = 1;
	g_bsem_fl = 1;
	cur_cmd->semafor = NULL;
	cur_cmd->bsemafor = NULL;
	cur_cmd->sem_name = NULL;
	cur_cmd->bsem_name = NULL;
}
