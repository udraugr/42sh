/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:48:56 by thaley            #+#    #+#             */
/*   Updated: 2019/12/27 14:04:55 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ws_is_bigger(void)
{
	tputs(tgoto(tgetstr("UP", NULL), 0, g_input->multiline.pos), 1, putint);
	tputs(tgetstr("cr", NULL), 1, putint);
	tputs(tgetstr("cd", NULL), 1, putint);
	ft_putstr_fd(g_input->prompt, STDERR_FILENO);
	ft_putstr_fd(g_input->input, STDERR_FILENO);
	g_input->curs_pos = g_input->input_len + g_input->prompt_len;
	null_multiline();
	count_lines();
}

void		ft_signal_win_size(int signo)
{
	int		ws;

	ws = g_input->ws.ws_col;
	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	if (ws > g_input->ws.ws_col)
	{
		null_multiline();
		count_lines();
		if (g_input->curs_pos - g_input->prompt_len < g_input->input_len\
		&& g_input->multiline.num_of_lines)
		{
			while (g_input->curs_pos < g_input->multiline.start\
					[g_input->multiline.pos])
				g_input->multiline.pos--;
		}
	}
	else
		ws_is_bigger();
}
