/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:21:27 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 16:40:25 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		go_home_pos(void)
{
	int		curs;
	int		y;

	y = g_input->multiline.pos;
	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == 0)
		return ;
	if (g_input->multiline.pos == 0)
		tputs(tgoto(tgetstr("ch", NULL), 0, g_input->prompt_len), 1, putint);
	else
	{
		tputs(tgoto(tgetstr("UP", NULL), 0, y), 1, putint);
		tputs(tgoto(tgetstr("ch", NULL), 0, g_input->multiline.start[0]),\
		1, putint);
	}
	g_input->multiline.pos = 0;
	g_input->curs_pos = g_input->prompt_len;
}

void		go_end_pos(void)
{
	int		curs;
	int		y;
	int		x;

	if (g_input->multiline.num_of_lines == 0)
		x = g_input->multiline.end[0];
	else
		x = g_input->multiline.end[g_input->multiline.num_of_lines]\
		- g_input->multiline.start[g_input->multiline.num_of_lines];
	y = g_input->multiline.num_of_lines - g_input->multiline.pos;
	curs = g_input->curs_pos - g_input->prompt_len;
	if (curs == g_input->input_len)
		return ;
	if (g_input->multiline.pos < g_input->multiline.num_of_lines)
		tputs(tgoto(tgetstr("DO", NULL), 0, y), 1, putint);
	tputs(tgoto(tgetstr("ch", NULL), 0, x), 1, putint);
	g_input->curs_pos = g_input->multiline.end[g_input->multiline.num_of_lines];
	g_input->multiline.pos = g_input->multiline.num_of_lines;
}
