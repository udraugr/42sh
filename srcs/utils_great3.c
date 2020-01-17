/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:25:30 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 17:23:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_greatflag	*ft_ini_great_fl(void)
{
	t_greatflag *f;

	if (!(f = malloc(sizeof(t_greatflag))))
		return (NULL);
	f->pref_fd = -7;
	f->file_redir = NULL;
	f->flag_all = 0;
	f->out_fd = -7;
	f->j = 0;
	return (f);
}

int			ft_tst_great_fd(t_greatflag *f, t_cmdlist *cmd, int i)
{
	f->j = f->ind - cmd->avcmd[i];
	f->flag_add = ft_set_flag_add(f->ind);
	if ((f->pref_fd = ft_set_pref_fd(cmd, i, f->j)) == -2)
		return (-1);
	if (cmd->avcmd[i][f->j + 1 + f->flag_add] == '&' && (f->flag_all = 1) &&
	cmd->avcmd[i][f->j + 2 + f->flag_add] != '-')
	{
		if ((int)ft_strlen(cmd->avcmd[i]) ==
			f->j + 1 + f->flag_all + f->flag_add)
		{
			if (ft_tst_great_fd_loop(cmd, i, f) == -1)
				return (-1);
		}
		else
		{
			if ((f->out_fd = ft_get_next_num(cmd->avcmd[i]
				+ f->j + 1 + f->flag_all + f->flag_add)) < 0 ||
			ft_test_fd(f->out_fd) == -1)
				return (-1);
		}
	}
	return (0);
}

int			ft_tst_great_getfile(t_greatflag *f, t_cmdlist *cmd, int i)
{
	int l;

	l = f->j + 1 + f->flag_all + f->flag_add;
	if (f->flag_all == 1 && cmd->avcmd[i][l] == '-' && (g_redir_block = 1))
		f->file_redir = ft_strdup("/dev/null");
	else if ((int)ft_strlen(cmd->avcmd[i]) > l)
	{
		f->file_redir = ft_get_sufx_name(cmd->avcmd[i], &(f->j), l);
		f->file_redir = ft_repl_tilda(f->file_redir, ft_strlen(f->file_redir));
	}
	else if (cmd->avcmd[i + 1])
		ft_tst_gf_norm(f, cmd, i, l);
	else
		return (ft_pr_msg_rc(" : parse error in command ", cmd->avcmd[i]));
	f->file_redir = del_ekran(f->file_redir);
	f->file_redir = ft_calc_full_path(f->file_redir);
	return (0);
}

int			ft_great_testfile(t_greatflag *f)
{
	if (f->file_redir && ft_test_file_mame(f->file_redir) == 0)
	{
		if (f->flag_add == 0 && (ft_strlen(f->file_redir) > 0))
			f->out_fd = open(f->file_redir,
										O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((ft_strlen(f->file_redir) > 0))
			f->out_fd = open(f->file_redir,
										O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (f->out_fd == -1)
		{
			ft_set_shell("?", "1");
			ft_print_msg(" : Error open file ", f->file_redir);
			free(f->file_redir);
			return (-1);
		}
		free(f->file_redir);
		f->file_redir = NULL;
		return (0);
	}
	free(f->file_redir);
	f->file_redir = NULL;
	return (-1);
}

int			ft_great_test_out(t_greatflag *f, t_cmdlist *cmd, int i)
{
	if (f->out_fd == -7)
	{
		if (ft_tst_great_getfile(f, cmd, i) == -1)
			return (-1);
		if (ft_great_testfile(f) == -1)
			return (-1);
	}
	return (0);
}
