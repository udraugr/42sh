/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_io_rest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:17:26 by wveta             #+#    #+#             */
/*   Updated: 2019/09/09 11:12:24 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_rest_in(t_cmdlist *cmd)
{
	if ((dup2(g_cmd->stdin_copy, STDIN_FILENO) == -1))
	{
		ft_print_msg(" : Error on restore ", "STDIN_FILENO");
		exit(1);
	}
	close(g_cmd->stdin_copy);
	cmd->fd0 = 0;
}

void	ft_rest_out(t_cmdlist *cmd)
{
	if ((dup2(g_cmd->stdout_copy, STDOUT_FILENO) == -1))
	{
		ft_print_msg(" : Error on restore ", "STDOUT_FILENO");
		exit(1);
	}
	close(g_cmd->stdout_copy);
	cmd->fd1 = 0;
}

void	ft_rest_err(t_cmdlist *cmd)
{
	if ((dup2(g_cmd->stderr_copy, STDERR_FILENO) == -1))
	{
		ft_print_msg(" : Error on restore ", "STDERR_FILENO");
		exit(1);
	}
	close(g_cmd->stderr_copy);
	cmd->fd2 = 0;
}
