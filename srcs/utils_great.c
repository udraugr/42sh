/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:30:15 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 16:45:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_set_flag_add(char *ind)
{
	if (ft_strncmp(ind, DGREAT, 2) != 0)
		return (0);
	else
		return (1);
}

int		ft_set_pref_fd(t_cmdlist *cmd, int i, int j)
{
	int			pref_fd;

	if (j == 0)
		pref_fd = 1;
	else if (j == 1 && cmd->avcmd[i][0] == '&')
		pref_fd = -1;
	else if (ft_isdigit(cmd->avcmd[i][j - 1]) == 1 && j > 0)
	{
		pref_fd = ft_get_prev_num(cmd->avcmd[i], j);
		if (ft_test_fd(pref_fd) == -1)
			return (-2);
	}
	else
		pref_fd = 1;
	return (pref_fd);
}

int		ft_test_fd(int fd)
{
	char		buf[5];
	char		*tmp;

	if (fd > 2)
	{
		if (read(fd, buf, 0) == -1)
		{
			tmp = ft_num_to_str(fd);
			ft_print_msg(" : Bad file descriptor ", tmp);
			free(tmp);
			return (-1);
		}
	}
	return (0);
}

int		ft_great_dup1(int pref_fd, int out_fd, t_cmdlist *cmd)
{
	if (pref_fd == 1 || pref_fd == -1)
	{
		if (cmd->fd1 == STDOUT_FILENO)
			g_cmd->stdout_copy = dup(STDOUT_FILENO);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			ft_print_msg(" : Bad file descriptor ", "");
			return (-1);
		}
		cmd->fd1 = out_fd;
		ft_redir_great_close(out_fd, STDOUT_FILENO);
	}
	if (pref_fd == 2)
	{
		if (cmd->fd2 == STDERR_FILENO)
			g_cmd->stderr_copy = dup(STDERR_FILENO);
		if (dup2(out_fd, STDERR_FILENO) == -1)
		{
			ft_print_msg(" : Err relink STDERR: ", "DUP2");
			return (-1);
		}
		cmd->fd2 = out_fd;
		ft_redir_great_close(out_fd, STDERR_FILENO);
	}
	return (0);
}

int		ft_great_dup2(int pref_fd, int out_fd, t_cmdlist *cmd)
{
	if (pref_fd != -1)
		return (0);
	if (cmd->fd1 == STDOUT_FILENO)
		g_cmd->stdout_copy = dup(STDOUT_FILENO);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		ft_print_msg(" : Err relink STDOUT: ", "DUP2");
		return (-1);
	}
	cmd->fd1 = out_fd;
	if (g_redir_block == 1)
		close(STDOUT_FILENO);
	if (cmd->fd2 == STDERR_FILENO)
		g_cmd->stderr_copy = dup(STDERR_FILENO);
	if (dup2(out_fd, STDERR_FILENO) == -1)
	{
		ft_print_msg(" : Err relink STDERR: ", "DUP2");
		return (-1);
	}
	cmd->fd2 = out_fd;
	if (out_fd > 2)
		close(out_fd);
	if (g_redir_block == 1)
		close(STDERR_FILENO);
	return (0);
}
