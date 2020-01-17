/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:15:41 by thaley            #+#    #+#             */
/*   Updated: 2019/12/27 12:03:08 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	prompt_len_color(char *prompt)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\e' && (prompt[i + 1] && prompt[i + 1] == '[') \
			&& (prompt[i + 2] && ft_isdigit(prompt[i + 2])))
		{
			while (prompt[i] && (i == 0 || prompt[i - 1] != 'm'))
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void		null_all(void)
{
	ft_bzero(g_input->input, MAX_CMDS);
	ft_bzero(g_input->old_input, MAX_CMDS);
	ft_bzero(g_input->copy, MAX_CMDS);
	g_input->autocompl.seach_res = NULL;
	null_autocmpl(0);
	g_input->prompt_len = prompt_len_color(g_input->prompt);
	g_input->curs_pos = g_input->prompt_len;
	g_input->input_len = 0;
	g_input->heredoc = 0;
	null_multiline();
	g_input->quotes = '\0';
	g_input->start_quotes = -1;
	g_input->old_in_check = 0;
}

static void	open_fd(void)
{
	char	*tmp;
	int		fd1;
	int		fd2;

	tmp = NULL;
	if (!isatty(STDIN_FILENO))
		exit(EXIT_FAILURE);
	if (!isatty(STDOUT_FILENO))
	{
		tmp = ttyname(STDIN_FILENO);
		fd1 = open(tmp, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd1 == -1)
			bad_fd_error(1, tmp);
	}
	if (!isatty(STDERR_FILENO))
	{
		tmp = ttyname(STDIN_FILENO);
		fd2 = open(tmp, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd2 == -1)
			bad_fd_error(2, tmp);
	}
}

void		init_input(char *prompt)
{
	open_fd();
	if (!g_hist)
		create_history();
	if (!(g_input = (t_input *)malloc(sizeof(t_input))))
		mall_check();
	g_input->prompt = ft_strdup(prompt);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	null_all();
	if (!ft_strncmp(prompt, "heredoc", 7))
		g_input->heredoc = 1;
}
