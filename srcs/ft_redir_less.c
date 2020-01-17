/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_less.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 11:02:25 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_fd_bynum(int i, int j, t_cmdlist *cmd)
{
	int			in_fd;

	in_fd = -1;
	if (cmd->avcmd[i][j + 1] == '&')
	{
		if ((int)ft_strlen(cmd->avcmd[i]) > j + 2)
		{
			if (ft_less_w0(&in_fd, i, j, cmd) == -2)
				return (-2);
		}
		else if (cmd->avcmd[i + 1])
		{
			if (ft_less_w1(&in_fd, i, cmd) == -2)
				return (-2);
		}
		else if (cmd->avcmd[i + 1] && cmd->avcmd[i + 1][0] == '-')
			return (0);
		else
		{
			ft_print_msg(" : parse error near :", cmd->avcmd[i] + j + 1);
			ft_set_shell("?", "1");
			return (-2);
		}
	}
	return (in_fd);
}

int		ft_get_next_num(char *s)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
		{
			ft_print_msg(" : parse error near :", s + i);
			ft_set_shell("?", "1");
			return (-1);
		}
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_get_prev_num(char *s, int k)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (i < k && s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (-1);
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_redir_less(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;
	int			in;

	j = 0;
	while (cmd->avcmd[i] && (ind = (ft_strchr(cmd->avcmd[i] + j, '<'))))
	{
		j = ind - cmd->avcmd[i];
		if (ft_check_ekran(cmd->avcmd[i], j) == 0 && (in = -1))
		{
			if (ft_strncmp(ind, LESS, 1) == 0 &&
				((int)ft_strlen(cmd->avcmd[i]) - 1 == j || (cmd->avcmd[i][j + 1]
				!= '<' && cmd->avcmd[i][j + 1] != '>')))
			{
				if (((in = ft_get_fd_bynum(i, j, cmd)) == -2) ||
				(in == -1 && ((in = ft_get_fd_by_n(i, cmd, ind, &j)) < 0)) ||
				(ft_fd_dup_close(in, i, j, cmd) == -1))
					return (-1);
			}
			j = -1;
		}
		j++;
	}
	return (0);
}
