/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:08:06 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 14:09:52 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			putint(int c)
{
	write(STDERR_FILENO, &c, 1);
	return (0);
}

void		move_left(void)
{
	if (g_input->curs_pos - g_input->prompt_len == 0)
		return ;
	if (g_input->curs_pos == g_input->multiline.start[g_input->multiline.pos]\
		&& g_input->multiline.pos > 0)
		move_end_of_line();
	else
	{
		g_input->curs_pos--;
		tputs(tgetstr("le", NULL), 1, putint);
	}
}

void		move_right(void)
{
	if (g_input->curs_pos - g_input->prompt_len == g_input->input_len)
		return ;
	if (g_input->curs_pos == g_input->multiline.end[g_input->multiline.pos]\
		&& g_input->multiline.pos < g_input->multiline.num_of_lines)
	{
		tputs(tgetstr("do", NULL), 1, putint);
		g_input->multiline.pos++;
		g_input->curs_pos++;
	}
	else
	{
		g_input->curs_pos++;
		tputs(tgetstr("nd", NULL), 1, putint);
	}
}

void		move_word_left(void)
{
	if (g_input->curs_pos - g_input->prompt_len == 0)
		return ;
	if (g_input->input[(g_input->curs_pos - g_input->prompt_len) - 1] < 33)
		move_left();
	while (g_input->curs_pos > g_input->prompt_len &&\
	g_input->input[g_input->curs_pos - g_input->prompt_len] < 33)
		move_left();
	while (g_input->curs_pos > g_input->prompt_len &&\
	g_input->input[(g_input->curs_pos - g_input->prompt_len) - 1] > 32)
		move_left();
}

void		move_word_right(void)
{
	int		curs;

	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == g_input->input_len)
		return ;
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len\
		&& g_input->input[g_input->curs_pos - g_input->prompt_len] > 32\
		&& g_input->input[g_input->curs_pos - g_input->prompt_len] < 127)
		move_right();
	while (g_input->curs_pos - g_input->prompt_len < g_input->input_len\
		&& g_input->input[g_input->curs_pos - g_input->prompt_len] < 33)
		move_right();
}
