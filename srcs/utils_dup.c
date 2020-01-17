/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:40:31 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 13:29:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_fd_dup_close(int in_fd, int i, int j, t_cmdlist *cmd)
{
	int	ret;

	ret = 0;
	if (cmd->fd0 == STDIN_FILENO)
		g_cmd->stdin_copy = dup(STDIN_FILENO);
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		ft_print_msg(" : Error link to STDIN: ", "DUP2");
		ret = -1;
	}
	cmd->fd0 = in_fd;
	close(in_fd);
	if (g_redir_block == 1 && g_parent_pid != getpid())
		close(STDIN_FILENO);
	if (j == 0 && cmd->avcmd[i][j] == '<')
		cmd->avcmd[i][j] = '\0';
	(void)j;
	(void)i;
	return (ret);
}

int		ft_fork(t_pipe *p_head)
{
	if ((p_head->cur_cmd->pid = fork()) < 0)
	{
		ft_print_msg(" : Error in function: ", "FORK");
		return (-1);
	}
	p_head->cur_cmd->pid_z = p_head->cur_cmd->pid;
	return (0);
}

void	ft_init_curcmd(t_cmdlist *cur_cmd)
{
	if (cur_cmd)
	{
		cur_cmd->next = NULL;
		cur_cmd->fd_pipe_in[0] = -1;
		cur_cmd->fd_pipe_in[1] = -1;
		cur_cmd->fd_pipe_out[0] = -1;
		cur_cmd->fd_pipe_out[1] = -1;
		cur_cmd->fd0 = STDIN_FILENO;
		cur_cmd->fd1 = STDOUT_FILENO;
		cur_cmd->fd2 = STDERR_FILENO;
		cur_cmd->here = NULL;
		cur_cmd->child_pid = -777;
		cur_cmd->andor = g_and_or;
		g_and_or = 0;
		cur_cmd->locals = NULL;
		cur_cmd->find_path = NULL;
		cur_cmd->pid_z = 0;
		cur_cmd->status = 0;
		cur_cmd->semafor = NULL;
		cur_cmd->sem_name = NULL;
		cur_cmd->bsemafor = NULL;
		cur_cmd->bsem_name = NULL;
	}
}

void	ft_set_cmd(t_pipe *p_head)
{
	if (!(p_head->first_cmd))
	{
		p_head->cur_cmd->nr = 1;
		p_head->first_cmd = p_head->cur_cmd;
		p_head->last_cmd = p_head->cur_cmd;
	}
	else
	{
		p_head->last_cmd->next = p_head->cur_cmd;
		p_head->cur_cmd->nr = p_head->last_cmd->nr + 1;
		p_head->last_cmd = p_head->cur_cmd;
	}
	ft_new_semafor(p_head->cur_cmd);
}

int		ft_test_cmd_pipe(char **av, int start, t_pipe *p)
{
	if (!(p->cur_cmd->avcmd = ft_get_pipe_av(av, start)))
		return (-1);
	p->cur_cmd->built_in = ft_test_built_in(p->cur_cmd->avcmd[0]);
	return (0);
}
