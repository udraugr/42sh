/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:13 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 17:30:04 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	remake_hist_file(char **tmp)
{
	int		fd;
	int		j;

	fd = 0;
	j = 0;
	fd = open(g_hist->path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd <= 0)
		return ;
	while (tmp[j])
	{
		write(fd, tmp[j], ft_strlen(tmp[j]));
		j++;
	}
	close(fd);
}

char		**remake_hist(void)
{
	int		i;
	int		j;
	char	**tmp;

	j = 0;
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * 101);
	while (++i < 101)
		tmp[i] = NULL;
	i = 0;
	ft_free(g_hist->cmd[i]);
	g_hist->cmd[i] = NULL;
	while (g_hist->cmd[++i])
	{
		tmp[j] = ft_strdup(g_hist->cmd[i]);
		j++;
		ft_free(g_hist->cmd[i]);
		g_hist->cmd[i] = NULL;
	}
	free(g_hist->cmd);
	g_hist->cmd = NULL;
	g_hist->amount = j;
	tmp[j] = NULL;
	remake_hist_file(tmp);
	return (tmp);
}

static void	write_in_matr(int len, char *buf)
{
	len = ft_strlen(buf);
	if (len == 0 && buf[0] == '\0')
		g_hist->cmd[g_hist->amount] = ft_strfjoin(\
				g_hist->cmd[g_hist->amount], "\n");
	else
		g_hist->cmd[g_hist->amount] = ft_strfjoin(\
				g_hist->cmd[g_hist->amount], buf);
	if (len >= 2 && buf[len - 2] == 7)
		g_hist->amount++;
	if (g_hist->amount == 100)
		g_hist->cmd = remake_hist();
}

static void	hist_from_file(void)
{
	int		len;
	int		fd;
	char	tmp[MAX_CMDS];
	char	*buf;

	buf = NULL;
	len = 0;
	ft_bzero(tmp, MAX_CMDS);
	fd = open(g_hist->path, O_RDONLY);
	if (fd < 1)
		return ;
	while ((get_next_line(fd, &buf)) > 0)
	{
		buf = ft_strfjoin(buf, "\n");
		write_in_matr(len, buf);
		free(buf);
		buf = NULL;
	}
	ft_strdel(&buf);
	close(fd);
	if (g_hist->cmd[g_hist->amount])
		free(g_hist->cmd[g_hist->amount]);
	g_hist->cmd[g_hist->amount] = NULL;
}

void		create_history(void)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (!(g_hist = (t_hist *)malloc(sizeof(t_hist))))
		mall_check();
	if (!(g_hist->cmd = (char **)malloc(sizeof(char *) * 101)))
		mall_check();
	while (++i < 101)
		g_hist->cmd[i] = NULL;
	if ((tmp = ft_get_my_home()))
	{
		g_hist->path = ft_strjoin(tmp, "/.history");
		free(tmp);
	}
	g_hist->amount = 0;
	hist_from_file();
	g_hist->pos = g_hist->amount;
}
