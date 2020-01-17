/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:34:55 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 14:56:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_setqflag(int *qflag, int val, int *wcount)
{
	*qflag = val;
	*wcount = *wcount + 1;
}

void		ft_ini_quoteflag_spl(t_quoteflag *f)
{
	f->i = 0;
	f->br_count = 0;
	f->br_flag = 0;
	f->qflag = 0;
	f->flsub = 0;
	f->b_sl = 0;
	f->i_cmd = 0;
	f->subs_end = -1;
	f->subs_start = -1;
}

char		**ft_init_matr(char **m, int i)
{
	int j;

	j = -1;
	while (++j < i)
		m[j] = NULL;
	return (m);
}

int			ft_get_word(char **ret, int count, int size, char const *s)
{
	ret[count] = ft_strndup(s, (size_t)(size));
	return (0);
}

char		**ft_split_pipes(char *s)
{
	int		count;
	char	**ret;
	int		myjob;

	if (!s || (count = ft_split_pipes_words(s)) == 0)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (ret == NULL)
		return (NULL);
	else
	{
		ret[count] = NULL;
		ret = ft_init_matr(ret, count);
		if (ft_all_pipe_words(ret, s) == -1 || ft_parse_pipe(ret))
		{
			ret = ft_free_char_matr(ret);
			return (NULL);
		}
	}
	myjob = g_job;
	ret = ft_cnt_subs(ret);
	g_job = myjob;
	ret = ft_resize_matr(ret);
	ret = ft_press_matr(ret);
	return (ret);
}
