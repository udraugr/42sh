/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 21:43:09 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_child_check_subsh(t_cmdlist *cur_cmd)
{
	while (cur_cmd->avcmd[0][0] && ft_isspace(cur_cmd->avcmd[0][0]))
		ft_strcpy(cur_cmd->avcmd[0], cur_cmd->avcmd[0] + 1);
	if (cur_cmd->avcmd[0][0] == '(' || cur_cmd->avcmd[0][0] == '{')
		return (1);
	return (0);
}

char		**ft_get_myalias(char **args)
{
	int i;

	i = -1;
	while (args && args[++i])
	{
		if (i == 0)
			args = ft_get_alias(args, i);
		else if (ft_strcmp(args[i], "|") == 0 && args[i + 1])
			args = ft_get_alias(args, i + 1);
	}
	return (args);
}

char		*ft_get_lpwd(char **locals)
{
	char *tmp;

	tmp = NULL;
	if (!((tmp = ft_get_env2("PWD", locals))))
	{
		if (!(tmp = ft_get_env("PWD")))
		{
			if (!(tmp = ft_strnew(255)))
				exit_shell(1);
			getcwd(tmp, 255);
		}
	}
	return (tmp);
}

int			ft_parse_if_4(char *str, t_quoteflag *f)
{
	int rc;

	if (f->qflag != 2 && str[f->i + f->i_cmd] == '\\' &&
	((f->b_sl = f->b_sl + 1)))
		f->b_sl = f->b_sl % 2;
	rc = ft_parse_if_3(f, str);
	return (rc);
}

t_cmdlist	*ft_child_pipe_row32(t_cmdlist *cur_cmd)
{
	int	i;

	if ((cur_cmd->avcmd = ft_all_calc_tst(cur_cmd->avcmd)) && g_calc != 0)
		exit(g_calc);
	if ((cur_cmd->here && ft_get_redir_hd(cur_cmd)))
		exit(1);
	cur_cmd = ft_local_assig(cur_cmd);
	if (!(cur_cmd->avcmd[0]))
	{
		cur_cmd->locals = ft_put_locals(cur_cmd->locals);
		exit(0);
	}
	cur_cmd->avcmd = ft_globbing(cur_cmd->avcmd);
	cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
	if (ft_do_redir(cur_cmd) != 0)
		exit(1);
	i = -1;
	while (cur_cmd->avcmd[++i])
		cur_cmd->avcmd[i] = del_ekran(cur_cmd->avcmd[i]);
	return (cur_cmd);
}
