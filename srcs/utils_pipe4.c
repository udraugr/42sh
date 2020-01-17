/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 17:04:52 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_set_nopipe_start(t_cmdlist *cur_cmd)
{
	int i;

	cur_cmd->avcmd = ft_all_calc_tst(cur_cmd->avcmd);
	if (g_calc != 0)
		return (-1);
	cur_cmd->avcmd = ft_globbing(cur_cmd->avcmd);
	cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
	if (g_subs_rc == 1)
		return (-1);
	cur_cmd = ft_local_assig(cur_cmd);
	if (!cur_cmd->avcmd || !cur_cmd->avcmd[0])
	{
		cur_cmd->locals = ft_put_locals(cur_cmd->locals);
		return (-1);
	}
	cur_cmd->built_in = ft_test_built_in(cur_cmd->avcmd[0]);
	if (ft_do_redir(cur_cmd) != 0)
		return (-1);
	i = -1;
	while (cur_cmd->avcmd[++i])
		cur_cmd->avcmd[i] = del_ekran(cur_cmd->avcmd[i]);
	g_nopipe_start = 0;
	return (0);
}
