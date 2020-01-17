/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:00:39 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 14:11:50 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		error_msg(int err, int num, t_shell *shell)
{
	if (num == 1 && err == 0)
		ft_print_msg("tgetent: there is no\
		such entry.", shell->term);
	else if (num == 1 && err == -1)
		ft_print_msg("tgetent: terminfo database could\
			not be found.", shell->term);
	else if (num == 2)
		ft_print_msg("tcgetattr: error.", NULL);
	else
		ft_print_msg("tcsetattr: error.", NULL);
	free_all(shell);
	return_func("\0", "exit");
}

t_shell		*init_term(t_shell *shell)
{
	int		error;

	error = 0;
	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		mall_check();
	if (!(shell->term = ft_get_env("TERM")))
		shell->term = ft_strdup("xterm-256color");
	error = tgetent(NULL, shell->term);
	if (error < 1)
		error_msg(error, 1, shell);
	error = tcgetattr(0, &shell->new_param);
	if (error < 0)
		error_msg(error, 2, shell);
	error = tcgetattr(0, &shell->old_param);
	if (error < 0)
		error_msg(error, 2, shell);
	shell->new_param.c_lflag &= ~(ICANON | ECHO | ISIG);
	shell->new_param.c_cc[VMIN] = 1;
	shell->new_param.c_cc[VTIME] = 0;
	tputs(tgetstr("ve", NULL), 1, putint);
	tputs(tgetstr("ae", NULL), 1, putint);
	error = tcsetattr(0, TCSADRAIN, &shell->new_param);
	if (error < 0)
		error_msg(error, 3, shell);
	return (shell);
}
