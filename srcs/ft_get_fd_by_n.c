/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd_by_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 11:01:31 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/27 17:13:08 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ft_action_in_ft_redir_fd(int i, t_cmdlist *cmd, int *j, int k)
{
	char		*fr;

	fr = ft_get_sufx_name(cmd->avcmd[i], j, k);
	fr = ft_repl_tilda(fr, ft_strlen(fr));
	return (fr);
}

static char		*ft_redir_fd(int i, t_cmdlist *cmd, char *ind, int *j)
{
	char		*file_redir;

	file_redir = 0;
	if (((int)ft_strlen(cmd->avcmd[i]) >= ind - cmd->avcmd[i] + 2) &&
		ft_strcmp(cmd->avcmd[i] + (ind - cmd->avcmd[i]) + 1, "&-") == 0 &&
		(file_redir = ft_strdup("/dev/null")))
	{
		ind = ft_strcpy(ind, ind + 3);
		*j = ft_strlen(cmd->avcmd[i]);
		g_redir_block = 1;
	}
	else if ((int)ft_strlen(cmd->avcmd[i]) > ind - cmd->avcmd[i] + 1)
		file_redir = ft_action_in_ft_redir_fd(i, cmd, j, 1);
	else if (cmd->avcmd[i + 1] && cmd->avcmd[i + 1][0] == '-' &&
		(file_redir = ft_strdup("/dev/null")))
	{
		cmd->avcmd[i + 1] = ft_strcpy(cmd->avcmd[i + 1], cmd->avcmd[i + 1] + 1);
		g_redir_block = 1;
	}
	else if (cmd->avcmd[i + 1])
		file_redir = ft_action_in_ft_redir_fd(i + 1, cmd, j, 0);
	else
		ft_print_msg(" : syntax error in command ", "");
	return (file_redir);
}

int				ft_get_fd_by_n(int i, t_cmdlist *cmd, char *ind, int *j)
{
	char		*file_redir;
	int			len;

	if ((file_redir = ft_redir_fd(i, cmd, ind, j)) == 0)
		return (-1);
	file_redir = del_ekran(file_redir);
	if (ft_test_file_mame(file_redir) != 0 && ft_free_ret(file_redir))
		return (-1);
	file_redir = ft_calc_full_path(file_redir);
	if ((len = open(file_redir, O_RDONLY, 0644)) == -1)
		ft_pr_msg_rc(" : Error open file ", file_redir);
	free(file_redir);
	return (len);
}
