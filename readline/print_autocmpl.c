/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_autocmpl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:38:22 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 14:12:00 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		return_cursor(void)
{
	int		i;

	i = 0;
	g_input->curs_pos = g_input->autocompl.save_curs;
	if (g_input->curs_pos - g_input->prompt_len < g_input->input_len)
	{
		while ((g_input->curs_pos - g_input->prompt_len)\
				+ i != g_input->input_len)
		{
			tputs(tgetstr("le", NULL), 1, putint);
			i++;
		}
	}
}

static void	finish_print(void)
{
	write(STDERR_FILENO, "\n", 1);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	ft_putstr_fd(g_input->input, STDERR_FILENO);
	return_cursor();
	null_autocmpl(1);
}

void		print_array_init(int *i, int *len, int *count, int *row)
{
	*i = 0;
	*len = 0;
	*count = 0;
	*row = g_input->autocompl.num_in_row;
	g_input->autocompl.save_curs = g_input->curs_pos;
}

void		print_array(char **arr)
{
	int			i;
	int			len;
	int			row;
	int			count;

	print_array_init(&i, &len, &count, &row);
	go_end_pos();
	write(STDERR_FILENO, "\n", 1);
	while (i < g_input->autocompl.amount && arr[i])
	{
		len = g_input->autocompl.max_len - ft_strlen(arr[i]);
		ft_putstr_fd(arr[i], STDERR_FILENO);
		while (len-- > 0)
			write(STDERR_FILENO, " ", 1);
		i += g_input->autocompl.col_pos;
		row--;
		if (row == 0 || ((g_input->autocompl.amount < i || !arr[i])\
			&& count < g_input->autocompl.col_pos - 1))
		{
			write(STDERR_FILENO, "\n", 1);
			row = g_input->autocompl.num_in_row;
			i = ++count;
		}
	}
	finish_print();
}

void		change_input(char **str, char *key)
{
	int		i;
	DIR		*dir;

	i = ft_strlen(g_input->autocompl.path) - 1;
	if (!g_input->autocompl.path || g_input->autocompl.path[i] != '/')
		g_input->autocompl.path = ft_strfjoin(g_input->autocompl.path, "/");
	g_input->autocompl.path = ft_strfjoin(g_input->autocompl.path, str[0]);
	dir = opendir(g_input->autocompl.path);
	if (dir)
	{
		closedir(dir);
		str[0] = ft_strfjoin(str[0], "/");
	}
	i = 0;
	if (key)
	{
		while (str[0][i] && key[i] && str[0][i] == key[i])
			i++;
	}
	print(str[0] + i);
	null_autocmpl(1);
}
