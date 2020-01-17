/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:47:27 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 18:13:29 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			check_input(char *str, int i)
{
	while (i >= 0)
	{
		if (!ft_isspace(str[i]))
			return (1);
		i--;
	}
	return (0);
}

void		add_to_hist(char *str)
{
	int		len;
	int		fd;

	len = ft_strlen(str) + 2;
	if (!check_input(str, len - 3))
		return ;
	if (g_hist->amount == 100)
		g_hist->cmd = remake_hist();
	g_hist->cmd[g_hist->amount] = ft_strnew(len);
	g_hist->cmd[g_hist->amount] = ft_strcpy(g_hist->cmd[g_hist->amount]\
								, str);
	g_hist->cmd[g_hist->amount][len - 2] = 7;
	g_hist->cmd[g_hist->amount][len - 1] = '\n';
	g_hist->amount++;
	g_hist->pos = g_hist->amount;
	g_hist->cmd[g_hist->amount] = NULL;
	if ((fd = open(g_hist->path, O_RDWR | O_CREAT |\
		O_APPEND, S_IRUSR | S_IWUSR)) <= 0)
		return ;
	write(fd, g_hist->cmd[g_hist->amount - 1],\
		ft_strlen(g_hist->cmd[g_hist->amount - 1]));
	close(fd);
}

char		*check_backslash(char *tmp)
{
	int		len;

	len = -1;
	while (tmp[++len] && tmp[len + 1])
	{
		if ((tmp[len] == '\\') && (tmp[len + 1] == '\n'))
		{
			ft_strcpy(tmp + len, tmp + len + 2);
			len--;
		}
	}
	return (tmp);
}

char		*return_func(char *str, char *input)
{
	char	*tmp;

	tmp = NULL;
	if (str[0] == ENTER && !str[1] && !g_input->heredoc\
		&& g_input->input_len > 0)
		add_to_hist(g_input->input);
	if (str[0] == 4 && !str[1] && g_input->heredoc)
		tmp = ft_strdup(str);
	else if (str[0] == 4 && !str[1])
	{
		tmp = ft_strdup("exit");
		add_to_hist(tmp);
	}
	else if (str[0] != 3)
	{
		tmp = ft_strdup(input);
		tmp = check_backslash(tmp);
	}
	if (str[0] == 3 && !str[1] && g_input->heredoc)
	{
		tmp = ft_strnew(1);
		tmp[0] = 3;
	}
	return (tmp);
}
