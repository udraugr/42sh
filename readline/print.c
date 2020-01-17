/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 21:09:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/27 17:13:40 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			new_row(int i, int curs, char *tmp)
{
	if (tmp[i] != '\n')
		tputs(tgetstr("sf", NULL), 1, putint);
	else if (tmp[i] == '\n' && curs == g_input->ws.ws_col)
		tputs(tgetstr("sf", NULL), 1, putint);
	curs = 0;
	g_input->multiline.end\
	[g_input->multiline.num_of_lines++] = g_input->curs_pos - 1;
	g_input->multiline.start\
	[g_input->multiline.num_of_lines] = g_input->curs_pos;
	return (curs);
}

void		print_loop(char *tmp, int curs)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '\n' || ft_isprint(tmp[i]))\
			&& g_input->input_len < MAX_CMDS)
		{
			g_input->input[(g_input->curs_pos - g_input->prompt_len)] = tmp[i];
			g_input->curs_pos++;
			curs++;
			ft_putchar_fd(tmp[i], STDERR_FILENO);
			if (curs == g_input->ws.ws_col || tmp[i] == '\n')
				curs = new_row(i, curs, tmp);
			g_input->input_len++;
		}
		if (g_input->input_len >= MAX_CMDS)
			ft_putchar_fd(tmp[i], STDERR_FILENO);
		i++;
	}
}

void		print(char *str)
{
	int		save_curs;
	int		curs;
	char	*tmp;
	char	buf[MAX_CMDS];

	tmp = NULL;
	if ((str = check_shift(str)) && str[0] == '\n' && ft_strlen(str) == 1)
		go_end_pos();
	save_curs = 0;
	ft_bzero(buf, MAX_CMDS);
	if (!str)
		return ;
	tmp = check_curs_pos(&save_curs, buf, str, tmp);
	curs = temp_cursor();
	tputs(tgetstr("cd", NULL), 1, putint);
	g_input->multiline.num_of_lines = g_input->multiline.pos;
	print_loop(tmp, curs);
	g_input->multiline.end[g_input->multiline.num_of_lines] = g_input->curs_pos;
	g_input->multiline.pos = g_input->multiline.num_of_lines;
	if (save_curs > 0)
	{
		while (g_input->curs_pos > save_curs)
			move_left();
	}
	free(tmp);
}
