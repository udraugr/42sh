/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 09:44:28 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_arr_fd(int code, int fd0[2], int fd1[2])
{
	if (code == 1 || code == 2)
	{
		fd1[0] = -1;
		fd1[1] = -1;
	}
	if (code == 0 || code == 2)
	{
		fd0[0] = -1;
		fd0[1] = -1;
	}
}

void	ft_set_cmd_pipe(int code, t_cmdlist *cur_cmd, int fd0[2], int fd1[2])
{
	if (code == 0)
	{
		cur_cmd->fd_pipe_in[0] = fd0[0];
		cur_cmd->fd_pipe_in[1] = fd0[1];
	}
	else if (code == 1)
	{
		cur_cmd->fd_pipe_in[0] = -1;
		cur_cmd->fd_pipe_in[1] = -1;
	}
	else if (code == 2)
	{
		cur_cmd->fd_pipe_in[0] = fd1[0];
		cur_cmd->fd_pipe_in[1] = fd1[1];
	}
	else
		ft_set_cmd_pipe_out(code, cur_cmd, fd0, fd1);
}

void	ft_set_cmd_pipe_out(int code, t_cmdlist *cur_cmd,
		int fd0[2], int fd1[2])
{
	if (code == 3)
	{
		cur_cmd->fd_pipe_out[0] = fd1[0];
		cur_cmd->fd_pipe_out[1] = fd1[1];
	}
	else if (code == 4)
	{
		cur_cmd->fd_pipe_out[0] = -1;
		cur_cmd->fd_pipe_out[1] = -1;
	}
	else if (code == 5)
	{
		cur_cmd->fd_pipe_out[0] = fd0[0];
		cur_cmd->fd_pipe_out[1] = fd0[1];
	}
}

void	ft_pipe_dup_ch_in(t_cmdlist *cur_cmd)
{
	if (cur_cmd->fd_pipe_in[0] != -1 && cur_cmd->fd_pipe_in[0] != 0)
	{
		if (dup2(cur_cmd->fd_pipe_in[0], STDIN_FILENO) == -1)
		{
			ft_print_msg(" : Error DUP to STDIN: ", "DUP2");
			exit(0);
		}
		close(cur_cmd->fd_pipe_in[0]);
		if (cur_cmd->fd_pipe_in[1] != -1)
			close(cur_cmd->fd_pipe_in[1]);
	}
}

void	ft_pipe_dup_ch_out(t_cmdlist *cur_cmd)
{
	if (cur_cmd->fd_pipe_out[1] != -1 && cur_cmd->fd_pipe_out[1] != 1)
	{
		if (dup2(cur_cmd->fd_pipe_out[1], STDOUT_FILENO) == -1)
		{
			ft_print_msg(" : Error DUP to STDOUT: ", "DUP2");
			exit(0);
		}
		close(cur_cmd->fd_pipe_out[1]);
		if (cur_cmd->fd_pipe_out[0] != -1)
			close(cur_cmd->fd_pipe_out[0]);
	}
}
