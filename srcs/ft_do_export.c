/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 10:00:32 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/27 13:51:52 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		set_shell_status(char *str, int j, int flag)
{
	char		*parm;
	char		*val;

	parm = ft_alloc_char(1 + j);
	parm[0] = '\0';
	parm = ft_strncpy(parm, str, j);
	val = ft_alloc_char(ft_strlen(str) - j);
	val[0] = '\0';
	val = ft_strcat(val, str + j + 1);
	val = del_ekran(val);
	ft_set_shell(parm, val);
	if (flag == 0)
		ft_exp_env(parm, val);
	free(parm);
	free(val);
}

void			ft_do_export(char *str, int flag, int j)
{
	int			i;
	char		*val;
	char		*tmp;

	i = ft_strlen(str);
	if (j == (int)ft_strlen(str) && flag == 0 &&
	((val = ft_get_env2(str, g_shell))))
	{
		tmp = ft_strdup(str);
		ft_exp_env(tmp, val);
		free(tmp);
		free(val);
	}
	else if (j != (int)ft_strlen(str))
		set_shell_status(str, j, flag);
	else if (j == (int)ft_strlen(str) && flag == 1)
		ft_unset_env_parm(str);
}

int				ft_test_f_andor(t_quoteflag *f, char *str)
{
	if ((int)ft_strlen(str) == f->i + f->i_cmd + 2)
	{
		ft_set_shell("?", "1");
		ft_print_msg(": parse error: ", str + f->i_cmd);
		g_and_or_line = 0;
		return (1);
	}
	return (0);
}
