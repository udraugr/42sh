/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_less2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 18:47:26 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_msg_c(char *s1, char *s2, int code)
{
	ft_set_shell("?", "1");
	ft_print_msg(s1, s2);
	return (code);
}

int		ft_less_w0(int *in_fd, int i, int j, t_cmdlist *cmd)
{
	char		buf[5];

	if (cmd->avcmd[i][j + 2] == '-')
		return (0);
	if ((*in_fd = ft_get_next_num(cmd->avcmd[i] + j + 2)) < 0)
	{
		cmd->avcmd[i][j] = '\0';
		return (-2);
	}
	cmd->avcmd[i][j] = '\0';
	if (*in_fd > 2 && read(*in_fd, buf, 0) == -1)
	{
		ft_print_msg(" : Bad file descriptor ", cmd->avcmd[i] + j + 2);
		ft_set_shell("?", "1");
		return (-2);
	}
	return (0);
}

int		ft_less_w1(int *in_fd, int i, t_cmdlist *cmd)
{
	char		buf[5];

	if (cmd->avcmd[i + 1][0] == '-')
		return (0);
	if ((*in_fd = ft_get_next_num(cmd->avcmd[i + 1])) < 0)
	{
		cmd->avcmd[i + 1][0] = '\0';
		return (-2);
	}
	if (*in_fd > 2 && read(*in_fd, buf, 0) == -1)
	{
		ft_set_shell("?", "1");
		ft_print_msg(" : Bad file descriptor ", cmd->avcmd[i + 1]);
		cmd->avcmd[i + 1][0] = '\0';
		return (-2);
	}
	cmd->avcmd[i + 1][0] = '\0';
	return (0);
}

int		ft_test_file_mame(char *fname)
{
	int i;

	i = -1;
	if (fname == NULL || fname[0] == '\0')
	{
		ft_print_msg(" : Syntax error near ", fname + i);
		ft_set_shell("?", "1");
		return (-1);
	}
	while (fname[++i])
	{
		if (ft_strchr("<>,();|!&", fname[i]) && !ft_check_ekran(fname, i))
		{
			ft_print_msg(" : Syntax error near ", fname + i);
			ft_set_shell("?", "1");
			return (-1);
		}
	}
	return (0);
}
