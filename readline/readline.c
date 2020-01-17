/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:09:43 by thaley            #+#    #+#             */
/*   Updated: 2019/12/27 12:15:35 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	is_end_char(char c)
{
	if (c == 3 || c == SET_COLOR || c == SET_SIG || c == 12)
		return (1);
	else if (c == 4 && !g_input->input_len)
		return (1);
	else if (c == ENTER && !parse_quotes())
		return (1);
	return (0);
}

int			is_print(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != 10 && str[i] < 32) || str[i] > 126)
			return (0);
		i++;
	}
	return (1);
}

char		*read_loop(void)
{
	char	c[4096];

	signal(SIGWINCH, ft_signal_win_size);
	while (1)
	{
		ft_bzero(c, 4096);
		read(STDIN_FILENO, &c, 4095);
		if (g_input->autocompl.tab_count == 1 && c[0] != TAB)
			null_autocmpl(1);
		if (match_key(c) || autocmp(c))
			continue ;
		else if (is_end_char(c[0]) && !c[1])
			return (return_func(c, g_input->input));
		else
			print(c);
	}
}

void		check_cursor(void)
{
	int		curs;

	curs = take_curs();
	if (curs != 1)
		write(STDERR_FILENO, "\n", 1);
}

char		*read_line(char *prompt)
{
	char	*ret;
	t_shell	*shell;

	ret = NULL;
	shell = NULL;
	init_input(prompt);
	shell = init_term(shell);
	check_cursor();
	ft_putstr_fd(prompt, STDERR_FILENO);
	ret = read_loop();
	go_end_pos();
	if (tcsetattr(0, TCSADRAIN, &shell->old_param) < 0)
		error_msg(-1, 3, shell);
	free_all(shell);
	write(1, "\n", 1);
	return (ret);
}
