/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_shellrev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/12/17 13:17:29 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_test_built_in(char *path)
{
	if (path && (
	(ft_strcmp(path, "exit") == 0) ||
	(g_envi->env && ft_strcmp(path, "set") == 0) ||
	(ft_strcmp(path, "cd") == 0) ||
	(ft_strcmp(path, "export") == 0) ||
	(ft_strcmp(path, "unset") == 0) ||
	(ft_strcmp(path, "echo") == 0) ||
	(ft_strcmp(path, "type") == 0) ||
	(ft_strcmp(path, "printenv") == 0) ||
	(ft_strcmp(path, "hash") == 0) ||
	(ft_strcmp(path, "jobs") == 0) ||
	(ft_strcmp(path, "fg") == 0) ||
	(ft_strcmp(path, "bg") == 0) ||
	(ft_strcmp(path, "kill") == 0) ||
	(ft_strcmp(path, "alias") == 0) ||
	(ft_strcmp(path, "unalias") == 0) ||
	(ft_strcmp(path, "test") == 0)))
		return (1);
	return (0);
}

t_cmdlist	*ft_free_cmd_list(t_cmdlist *first)
{
	t_cmdlist	*cur;
	t_cmdlist	*tmp;

	cur = first;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->avcmd)
			ft_free_char_matr(tmp->avcmd);
		if (tmp->locals)
			ft_free_char_matr(tmp->locals);
		if (tmp->find_path)
			free(tmp->find_path);
		if (tmp->here)
			free(tmp->here);
		ft_del_semafor(tmp);
		free(tmp);
	}
	return (NULL);
}

void		ft_do_cmd_list(t_pipe *p_head, int flpi)
{
	int				fd0[2];
	int				fd1[2];
	struct termios	tmodes;

	ft_init_arr_fd(2, fd0, fd1);
	ft_do_cmd_list_ini(p_head, flpi);
	tcgetattr(0, &tmodes);
	if (ft_do_cmd_loop(p_head, fd0, fd1, flpi) == -1)
	{
		tcsetattr(0, TCSADRAIN, &tmodes);
		g_pipe = NULL;
		return ;
	}
	ft_parent_wait(p_head, flpi);
	tcsetattr(0, TCSADRAIN, &tmodes);
	g_pipe = NULL;
}

void		ft_do_cmd_shell(char **av, int start, int flagpipe)
{
	int			nextpipe;
	t_pipe		*p_head;
	int			fl;

	p_head = ft_init_p_head(NULL, NULL);
	while ((start == 0 || av[start - 1]) && av[start])
	{
		fl = 0;
		if (!(p_head->cur_cmd = malloc(sizeof(t_cmdlist))))
			break ;
		ft_init_curcmd(p_head->cur_cmd);
		ft_set_cmd(p_head);
		if (((nextpipe = ft_get_count_in_pipe(av, start)) < 1 && flagpipe > 0)
			|| (ft_test_cmd_pipe(av, start, p_head) == -1))
			break ;
		fl = 1;
		if (flagpipe > 0)
			start = start + nextpipe + 1;
		else
			break ;
	}
	if (fl == 1)
		ft_do_cmd_list(p_head, flagpipe);
	p_head->first_cmd = ft_free_cmd_list(p_head->first_cmd);
	free(p_head);
}
