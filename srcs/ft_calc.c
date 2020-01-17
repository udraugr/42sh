/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 20:45:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "calc/include/arithmetic.h"

char	*ft_calc_str(char *str, char *pref, char *suff, char *tmp)
{
	str[0] = '\0';
	str = ft_strfjoin(str, pref);
	str = ft_strfjoin(str, tmp);
	str = ft_strfjoin(str, suff);
	return (str);
}

char	**ft_tst_calc(char **str, int n, int start, int end)
{
	char	*tmp;
	char	*pref;
	char	*suff;

	if (start == -1 || end == -1)
		return (str);
	pref = NULL;
	suff = NULL;
	if (end - start > 1)
	{
		if (start > 2)
			pref = ft_strndup(str[n], start - 1);
		if (str[n][end + 1] != '\0')
			suff = ft_strdup(str[n] + end + 1);
		tmp = ft_strdup(str[n] + start + 2);
		tmp[end - start - 3] = '\0';
		tmp = ft_replays(tmp);
		if (ft_check_ekran(pref, ft_strlen(pref)) < 2 && ((tmp = ft_calc(tmp))))
			str[n] = ft_calc_str(str[n], pref, suff, tmp);
		free(tmp);
		free(pref);
		free(suff);
	}
	return (str);
}

char	**ft_all_calc_tst(char **str)
{
	t_quoteflag	*f;

	f = ft_get_quoteflag();
	f->n = -1;
	g_calc = 0;
	while (str && str[++f->n])
	{
		ft_ini_quoteflag(f);
		while (str[f->n][++f->i])
		{
			ft_set_b_sl(f, str);
			if (f->qflag == 0)
				ft_cacl_test_b(f, str[f->n]);
			if (((str = ft_test_calc(f, str))) && f->rc == 1 && ft_free_qf(f))
				return (str);
			else if (f->rc == 2)
				continue;
			ft_calc_test_q(f, str[f->n]);
			ft_test_doll_calc(f, str);
			if (f->qflag != 2 && str[f->n][f->i] != '\\' && f->b_sl == 1)
				f->b_sl = 0;
		}
	}
	free(f);
	return (str);
}

char	*ft_calc_subs(char *s)
{
	char	**ret;

	if (!s)
		return (s);
	if (!(ret = (char **)malloc(sizeof(char *) * 2)))
		exit(1);
	ret[0] = ft_strdup(s);
	ret[1] = NULL;
	ret = ft_cnt_subs(ret);
	free(s);
	s = ft_strdup(ret[0]);
	ft_free_char_matr(ret);
	return (s);
}

char	*ft_calc(char *str)
{
	char	*ans;

	str = ft_calc_subs(str);
	str = ft_calc_in_calc(str);
	ans = calculator(str);
	if (ans)
	{
		ft_strdel(&str);
		str = ans;
	}
	else
	{
		g_calc = 1;
		ft_set_shell("?", "1");
	}
	return (str);
}
