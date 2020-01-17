/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:01:14 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 18:28:30 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		free_all(t_shell *shell)
{
	int		i;

	i = -1;
	if (shell)
	{
		ft_free(shell->term);
		free(shell);
	}
	if (g_hist)
	{
		while (g_hist->cmd[++i])
			ft_free(g_hist->cmd[i]);
		free(g_hist->cmd);
		ft_free(g_hist->path);
		free(g_hist);
	}
	if (g_input)
	{
		ft_free(g_input->prompt);
		free(g_input);
	}
	shell = NULL;
	g_hist = NULL;
	g_input = NULL;
}

void		ft_free(char *str)
{
	if (str != NULL)
		free(str);
}

void		null_autocmpl(int time)
{
	int		i;

	i = 0;
	if (g_input->autocompl.seach_res && time)
	{
		while (g_input->autocompl.seach_res[i])
		{
			free(g_input->autocompl.seach_res[i]);
			g_input->autocompl.seach_res[i++] = NULL;
		}
		free(g_input->autocompl.seach_res);
	}
	if (time)
		ft_free(g_input->autocompl.path);
	g_input->autocompl.path = NULL;
	g_input->autocompl.seach_res = NULL;
	g_input->autocompl.amount = 0;
	g_input->autocompl.cmd = 0;
	g_input->autocompl.file = 0;
	g_input->autocompl.key_check = 0;
	g_input->autocompl.save_curs = 0;
	g_input->autocompl.tab_count = 0;
	g_input->autocompl.max_len = 0;
	g_input->autocompl.num_in_row = 0;
	g_input->autocompl.col_pos = 0;
}

void		null_multiline(void)
{
	g_input->multiline.num_of_lines = 0;
	g_input->multiline.pos = 0;
	ft_bzero(g_input->multiline.start, MAX_CMDS);
	ft_bzero(g_input->multiline.end, MAX_CMDS);
	g_input->multiline.start[0] = g_input->prompt_len;
}
