/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_great.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 23:40:23 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_redir_great_n(t_greatflag *f, t_cmdlist *cmd, int i)
{
	if ((ft_tst_great_fd(f, cmd, i) == -1) ||
	(ft_great_test_out(f, cmd, i) == -1) ||
	(ft_great_dup1(f->pref_fd, f->out_fd, cmd) == -1))
	{
		free(f);
		return (-1);
	}
	return (0);
}

int		ft_redir_great(t_cmdlist *cmd, int i)
{
	t_greatflag	*f;
	char		*tmp;
	int			j;

	j = 0;
	while (cmd->avcmd[i] && (tmp = (ft_strchr(cmd->avcmd[i] + j, '>'))))
	{
		j = tmp - cmd->avcmd[i];
		if (ft_check_ekran(cmd->avcmd[i], tmp - cmd->avcmd[i]) == 0)
		{
			if (!(f = ft_ini_great_fl()))
				return (ft_print_msg(" : Error malloc ", "ft_redir_great"));
			f->ind = (ft_strchr(cmd->avcmd[i] + j, '>'));
			if (ft_redir_great_n(f, cmd, i) < 0)
				return (-1);
			ft_reset_cmd_great(f->j, i, cmd);
			free(f);
			j = -1;
		}
		j++;
	}
	return (0);
}
