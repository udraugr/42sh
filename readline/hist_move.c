/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:49:20 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 14:11:32 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	print_move_curs_back(char *tmp)
{
	go_home_pos();
	tputs(tgetstr("cd", NULL), 1, putint);
	g_input->input_len = 0;
	null_multiline();
	if (tmp && tmp[0] != '\0')
		print(tmp);
	if (g_input->multiline.num_of_lines)
	{
		go_home_pos();
		while (g_input->curs_pos < g_input->multiline.end[0])
			move_right();
	}
}

static void	input_from_hist(char *hist, int old)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(hist, 0, ft_strlen(hist) - 2);
	if (g_input->old_input[0] == '\0' && !g_input->old_in_check)
	{
		ft_strcpy(g_input->old_input, g_input->input);
		g_input->old_in_check = 1;
	}
	if (g_input->input_len > 0)
		ft_bzero(g_input->input, MAX_CMDS);
	print_move_curs_back(tmp);
	if (old)
	{
		ft_bzero(g_input->old_input, MAX_CMDS);
		g_input->old_in_check = 0;
	}
	free(tmp);
}

void		hist_move(int direction)
{
	if (g_input->multiline.pos ||\
	(g_input->input_len > 0 && !g_input->old_in_check))
		return ;
	if ((!direction && g_hist->pos == 0) ||\
	(direction && g_hist->pos == g_hist->amount))
		return ;
	if (direction && g_hist->pos < g_hist->amount)
		g_hist->pos++;
	else if (!direction && g_hist->pos > 0)
		g_hist->pos--;
	if (g_hist->pos == g_hist->amount && !g_hist->cmd[g_hist->pos])
		input_from_hist(g_input->old_input, 1);
	else
		input_from_hist(g_hist->cmd[g_hist->pos], 0);
}
