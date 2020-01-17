/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:26:47 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 16:41:28 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_line_up(void)
{
	int		i;
	int		prompt;

	i = 0;
	prompt = -1;
	if (g_input->multiline.pos == 0)
		return ;
	while ((g_input->curs_pos - i) >\
		g_input->multiline.start[g_input->multiline.pos])
		i++;
	tputs(tgetstr("up", NULL), 1, putint);
	tputs(tgetstr("cr", NULL), 1, putint);
	g_input->multiline.pos--;
	g_input->curs_pos = g_input->multiline.start[g_input->multiline.pos];
	if (g_input->multiline.pos == 0)
	{
		while (++prompt < g_input->prompt_len)
			tputs(tgetstr("nd", NULL), 1, putint);
	}
	while (i > 0 && g_input->curs_pos <\
		g_input->multiline.end[g_input->multiline.pos])
	{
		i--;
		move_right();
	}
}

void		move_line_down(void)
{
	int		i;

	i = 0;
	if (g_input->multiline.pos == g_input->multiline.num_of_lines)
		return ;
	while ((g_input->curs_pos - i) >\
		g_input->multiline.start[g_input->multiline.pos])
		i++;
	tputs(tgetstr("do", NULL), 1, putint);
	g_input->multiline.pos++;
	g_input->curs_pos = g_input->multiline.start[g_input->multiline.pos];
	while (i > 0 && g_input->curs_pos <\
		g_input->multiline.end[g_input->multiline.pos])
	{
		i--;
		move_right();
	}
}

void		move_end_of_line(void)
{
	int		i;

	i = -1;
	tputs(tgetstr("up", NULL), 1, putint);
	g_input->curs_pos--;
	g_input->multiline.pos--;
	if (g_input->multiline.pos == 0)
		i = (g_input->multiline.end[g_input->multiline.pos] -\
		g_input->multiline.start[g_input->multiline.pos])\
		+ g_input->prompt_len;
	else
		i = g_input->multiline.end[g_input->multiline.pos] -\
		g_input->multiline.start[g_input->multiline.pos];
	if (i > 0)
		tputs(tgoto(tgetstr("ch", NULL), 0, i), 1, putint);
}

void		cursor_back(void)
{
	int		curs;

	curs = g_input->curs_pos;
	tputs(tgetstr("cr", NULL), 1, putint);
	tputs(tgetstr("cd", NULL), 1, putint);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	ft_putstr_fd(g_input->input, STDERR_FILENO);
	if (g_input->curs_pos - g_input->prompt_len == g_input->input_len)
		return ;
	g_input->curs_pos = g_input->input_len + g_input->prompt_len;
	g_input->multiline.pos = g_input->multiline.num_of_lines;
	while (g_input->curs_pos > curs)
		move_left();
}

void		scroll_top(void)
{
	int		curs;
	int		i;
	char	buf[20];

	i = 0;
	curs = 0;
	ft_bzero(buf, 20);
	ft_putstr_fd("\e[6n", STDIN_FILENO);
	read(STDIN_FILENO, &buf, 20);
	while (buf[i] && !ft_isdigit(buf[i]))
		i++;
	curs = ft_atoi(buf + i);
	if (curs == 1)
		return ;
	while (curs > 0)
	{
		ft_putstr_fd(tgetstr("sr", NULL), STDERR_FILENO);
		curs--;
	}
	cursor_back();
}
