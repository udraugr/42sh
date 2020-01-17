/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_2less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 10:42:24 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_redir_hd(t_cmdlist *cmd)
{
	int		j;
	char	*heof;
	char	*tmp;

	heof = ft_alloc_char(500);
	heof[0] = '\0';
	tmp = ft_get_my_home();
	heof = ft_strcat(heof, tmp);
	free(tmp);
	heof = ft_strcat(heof, "/.c");
	j = open(heof, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(j, cmd->here, ft_strlen(cmd->here));
	free(cmd->here);
	cmd->here = heof;
	close(j);
	j = open(heof, O_RDONLY, 0644);
	g_cmd->stdin_copy = dup(STDIN_FILENO);
	if (dup2(j, STDIN_FILENO) == -1)
	{
		ft_print_msg(" : Error relink to STDIN: ", "DUP2");
		return (-1);
	}
	cmd->fd0 = j;
	close(j);
	return (0);
}

int		ft_redir_2less_n(t_cmdlist *cmd, int i, int j, char *ind)
{
	char		*heof;

	if (!(heof = ft_get_heof(ind, cmd, i, j)))
		return (-1);
	cmd->here = ft_heredoc(heof);
	free(heof);
	return (ft_get_redir_hd(cmd));
}

int		ft_redir_2less(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;

	j = 0;
	while (cmd->avcmd[i] && (ind = (ft_strchr(cmd->avcmd[i] + j, '<'))))
	{
		j = ind - cmd->avcmd[i];
		if (ft_check_ekran(cmd->avcmd[i], j) == 0)
		{
			j = ind - cmd->avcmd[i];
			if (ft_strncmp(ind, TLESS, 3) == 0)
			{
				if (ft_get_tless(cmd, i, j, ind) == -1)
					return (-1);
				return (ft_get_redir_hd(cmd));
			}
			else if (ft_strncmp(ind, DLESS, 2) == 0
			&& cmd->avcmd[i][j + 2] != '<')
				return (ft_redir_2less_n(cmd, i, j, ind));
			return (0);
		}
		j++;
	}
	return (0);
}

char	*ft_heredoc(char *eof)
{
	char	*tmp;
	char	*line;

	tmp = ft_memalloc(4096);
	while (1)
	{
		signal(SIGINT, ft_signal_handler_rl);
		line = read_line("heredoc> ");
		if (!(line))
		{
			tmp = ft_strcat(tmp, "\n");
			continue ;
		}
		else if (ft_strcmp(eof, line) != 0 && line[0] != 4 && line[0] != 3)
		{
			tmp = ft_strcat(tmp, line);
			tmp = ft_strcat(tmp, "\n");
		}
		else
		{
			free(line);
			return (tmp);
		}
		free(line);
	}
}
