/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:39:53 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 17:49:35 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmdlist	*ft_redir_init(t_cmdlist *cmd)
{
	cmd->fd0 = STDIN_FILENO;
	cmd->fd1 = STDOUT_FILENO;
	cmd->fd2 = STDERR_FILENO;
	return (cmd);
}

t_cmdlist	*ft_redir_io_restore(t_cmdlist *cmd)
{
	if (cmd->fd0 != STDIN_FILENO)
		ft_rest_in(cmd);
	if (cmd->fd1 != STDOUT_FILENO)
		ft_rest_out(cmd);
	if (cmd->fd2 != STDERR_FILENO)
		ft_rest_err(cmd);
	cmd->fd0 = 0;
	cmd->fd1 = 1;
	cmd->fd2 = 2;
	return (cmd);
}

int			ft_do_redir(t_cmdlist *cmd)
{
	int		i;
	char	*tmp;
	int		j;

	i = -1;
	while (cmd->avcmd[++i])
	{
		g_redir_block = 0;
		j = 0;
		while (ft_strlen(cmd->avcmd[i] + j) > 0 &&
		((tmp = (ft_strchr(cmd->avcmd[i] + j, '>'))) ||
		(tmp = (ft_strchr(cmd->avcmd[i] + j, '<')))))
		{
			j = tmp - cmd->avcmd[i];
			if (ft_check_ekran_full(cmd->avcmd[i], j) == 0)
			{
				if ((ft_redir_2less(cmd, i) < 0 || ft_redir_less(cmd, i) < 0 ||
				ft_redir_great(cmd, i) < 0) && (cmd = ft_redir_io_restore(cmd)))
					return (-1);
			}
			j++;
		}
	}
	cmd->avcmd = ft_press_matr(cmd->avcmd);
	return (0);
}

char		**ft_press_matr_up(char **matr, int count, int good)
{
	int		i;
	char	**tmp;

	i = -1;
	if ((good < count) && (tmp = malloc(sizeof(char *) * (good + 1))))
	{
		tmp[good] = NULL;
		i = 0;
		good = 0;
		while (i < count)
		{
			if (matr[i][0] != '\0')
				tmp[good++] = matr[i];
			else
				free(matr[i]);
			i++;
		}
		free(matr);
		matr = tmp;
	}
	return (matr);
}

char		**ft_press_matr(char **matr)
{
	int count;
	int good;

	if (matr)
	{
		good = 0;
		count = 0;
		while (matr[count])
		{
			if (matr[count][0] != '\0')
				good++;
			count++;
		}
		if (good != count)
			matr = ft_press_matr_up(matr, count, good);
	}
	return (matr);
}
