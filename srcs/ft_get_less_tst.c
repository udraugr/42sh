/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_less_tst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 23:47:41 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_tless(t_cmdlist *cmd, int i, int j, char *ind)
{
	if ((int)ft_strlen(cmd->avcmd[i]) > j + 3)
		cmd->here = ft_strdup(ind + 3);
	else
	{
		if (cmd->avcmd[i + 1])
		{
			cmd->here = ft_strdup(cmd->avcmd[i + 1]);
			cmd->avcmd[i + 1][0] = '\0';
		}
		else
		{
			ft_print_msg(" : sintax error in command: ", cmd->avcmd[i]);
			return (-1);
		}
	}
	ind[0] = '\0';
	cmd->here = ft_replays(cmd->here);
	return (ft_test_file_mame(cmd->here));
}

int		ft_redir_2lesshd_n(t_cmdlist *cmd, char *ind, int i, int j)
{
	int		j1;
	char	*tmp;
	char	*tmp2;

	if (!(tmp = ft_get_heof(ind, cmd, i, j)))
		return (-1);
	tmp2 = ft_heredoc(tmp);
	free(tmp);
	tmp = ft_strdup("/tmp/");
	tmp = ft_add_strnum(tmp, getpid());
	tmp = ft_strfjoin(tmp, "_h");
	tmp = ft_add_strnum(tmp, g_subs_counter);
	g_subs_counter++;
	j1 = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(j1, tmp2, ft_strlen(tmp2));
	free(tmp2);
	close(j1);
	tmp2 = ft_strndup(cmd->avcmd[i], j);
	tmp2 = ft_strfjoin(tmp2, "<");
	tmp2 = ft_strfjoin(tmp2, tmp);
	free(tmp);
	tmp2 = ft_strfjoin(tmp2, cmd->avcmd[i] + j);
	free(cmd->avcmd[i]);
	cmd->avcmd[i] = tmp2;
	return (0);
}

int		ft_redir_2lesshd(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;

	j = 0;
	while (cmd->avcmd[i] && (ind = (ft_strstr(cmd->avcmd[i] + j, "<<"))))
	{
		j = ind - cmd->avcmd[i];
		if (ft_check_ekran(cmd->avcmd[i], j) == 0)
		{
			if (ft_strncmp(ind, DLESS, 2) == 0
			&& cmd->avcmd[i][j + 2] != '<')
			{
				if (ft_redir_2lesshd_n(cmd, ind, i, j) == -1)
					return (-1);
				j = -1;
			}
			else
				return (0);
		}
		j++;
	}
	return (0);
}

int		ft_get_heretext(t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->avcmd[i])
	{
		if (ft_redir_2lesshd(cmd, i) == -1)
			return (-1);
		i++;
	}
	cmd->avcmd = ft_press_matr(cmd->avcmd);
	return (0);
}
