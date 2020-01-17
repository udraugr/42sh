/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 20:07:06 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipeflag	*ft_pipe_split_ini(void)
{
	t_pipeflag	*fl;

	fl = malloc(sizeof(t_pipeflag));
	fl->i = -1;
	fl->count = 0;
	fl->flag = 0;
	fl->qflag = 0;
	fl->br_count = 0;
	fl->br_flag = 0;
	fl->flsub = 0;
	fl->b_sl = 0;
	return (fl);
}

void		ft_pipe_split_3(t_pipeflag *fl, char **ret, char const *str)
{
	if (fl->flag == 1)
	{
		ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
		fl->count++;
	}
	ft_get_word(ret, fl->count, 1, str + fl->i);
	fl->count++;
	fl->flag = 0;
}

void		ft_pipe_split_4(t_pipeflag *fl, char **ret, char const *str)
{
	ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
	fl->count++;
	fl->flag = 0;
}

void		ft_pipe_split_sp(t_pipeflag *fl, char **ret, char const *str)
{
	if (fl->i > 0 && str[fl->i - 1] != ' ')
		ft_pipe_split_4(fl, ret, str);
	fl->start = fl->i;
}

char		ft_get_nextp_world(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isspace(s[i]) == 0)
			return (s[i]);
	return (0);
}
