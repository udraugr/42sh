/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntrl_subst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 19:42:51 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 20:34:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_read_subst(int fd, int vid, char *str)
{
	struct timespec	clock1;
	struct timespec	clock2;
	char			buf[2];

	clock1.tv_nsec = 100000000;
	clock1.tv_sec = 0;
	nanosleep(&clock1, &clock2);
	buf[0] = '\0';
	while (read(fd, &buf, 1) > 0)
	{
		buf[1] = '\0';
		if (vid == 0 && buf[0] == '\n')
			buf[0] = ' ';
		str = ft_strfjoin(str, buf);
		buf[0] = '\0';
	}
	if (ft_strlen(str) > 0)
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

char	*ft_go_subst(char *str, int vid)
{
	char			*tmp;
	int				fd;
	char			*wk;

	tmp = ft_strdup(">/tmp/");
	tmp = ft_add_strnum(tmp, getpid());
	tmp = ft_strfjoin(tmp, "_");
	tmp = ft_add_strnum(tmp, g_subs_counter);
	g_subs_counter++;
	wk = ft_strdup(str);
	wk = ft_strfjoin(wk, " ");
	wk = ft_strfjoin(wk, tmp);
	free(str);
	str = wk;
	g_pr_wait = 1;
	ft_parse_line(str);
	g_pr_wait = 0;
	str[0] = '\0';
	if ((fd = open(tmp + 1, O_RDONLY, 0644)) > -1 &&
		(str = ft_read_subst(fd, vid, str)))
		close(fd);
	free(tmp);
	return (str);
}

char	**ft_cnt_subs_exe(char **str, int n, int start, int end)
{
	char	*tmp;
	char	*pref;
	char	*suff;

	if (start == -1 || end == -1 || start == end - 1)
		return (str);
	pref = NULL;
	suff = NULL;
	if (end - start > 1 && str[n][start + 1] != '(')
	{
		if (start > 1)
			pref = ft_strndup(str[n], start - 1);
		if (str[n][end + 1] != '\0')
			suff = ft_strdup(str[n] + end + 1);
		tmp = ft_strdup(str[n] + start + 1);
		tmp[end - start - 1] = '\0';
		tmp = ft_go_subst(tmp, ft_check_ekran(str[n], start - 1));
		str[n][0] = '\0';
		str[n] = ft_strfjoin(ft_strfjoin(str[n], pref), tmp);
		str[n] = ft_strfjoin(str[n], suff);
		free(tmp);
		free(pref);
		free(suff);
	}
	return (str);
}

char	**ft_cnt_subs_tst(char **str, int n)
{
	t_quoteflag	*f;

	f = ft_get_quoteflag();
	ft_ini_quoteflag(f);
	while (str && str[n] && str[n][++f->i])
	{
		ft_subst_tst_ps(f, str, n);
		if (ft_subst_tst_exe(f, str, n) == 1)
			continue;
		ft_subst_tst_pf(f, str, n);
	}
	free(f);
	return (str);
}

char	**ft_cnt_subs(char **av)
{
	int		i;
	char	*gs;
	int		gl;

	i = -1;
	while (av && av[++i])
	{
		g_subst++;
		gs = g_job_start;
		gl = g_job_end;
		av = ft_cnt_subs_tst(av, i);
		g_job_start = gs;
		g_job_end = gl;
		g_subst--;
	}
	return (av);
}
