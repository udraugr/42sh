/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words_cut3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 12:36:21 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_get_words(void)
{
	return (0);
}

void		ft_pipe_split_sps(t_pipeflag *fl, char const *str)
{
	if (fl->i > 0 && str[fl->i - 1] != ' ')
		ft_pipe_split_4s(fl, str);
	fl->start = fl->i;
}

void		ft_pipe_split_4s(t_pipeflag *fl, char const *str)
{
	ft_get_words();
	fl->count++;
	fl->flag = 0;
	(void)str;
}

void		ft_pipe_split_3s(t_pipeflag *fl, char const *str)
{
	if (fl->flag == 1)
	{
		ft_get_words();
		fl->count++;
	}
	ft_get_words();
	fl->count++;
	fl->flag = 0;
	(void)str;
}

int			ft_check_pipe_n(char *str, t_quoteflag *f)
{
	if (ft_strlen(str) > (size_t)(f->i_cmd + f->i + 1) &&
			ft_get_nextp_world(str + f->i_cmd + f->i + 2) == '|')
	{
		ft_set_shell("?", "1");
		ft_print_msg(": parse error: ", str + f->i_cmd);
		g_and_or_line = 0;
		return (1);
	}
	return (0);
}
