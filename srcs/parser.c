/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:17:45 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 17:13:40 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_parser_go(char *cmd, char *str)
{
	char **args;

	if (ft_split_pipes_words(cmd) != 0)
	{
		args = ft_split_pipes(cmd);
		if (!args)
			return (1);
		args = ft_get_myalias(args);
		if (args && args[0])
		{
			if (ft_strlen(args[0]) > 0)
				ft_do_cmd_shell(args, 0, ft_test_pipe(args, 0));
			args = ft_free_char_matr(args);
		}
		else
		{
			ft_print_msg(": parse error near ", str);
			args = ft_free_char_matr(args);
			return (1);
		}
	}
	else if (g_parent_pid != getpid())
		ft_pr_msg_rc(" : syntax error : ", str);
	return (0);
}

char		*ft_get_file_path(char *path, t_listf *first_list)
{
	t_listf			*cur;
	char			*ret;
	unsigned int	hash;

	if (!(path) || !(cur = first_list))
		return (NULL);
	if ((ret = ft_get_hash_path(path)))
		return (ret);
	hash = hashly(path);
	while (cur)
	{
		if (hash == cur->hash && ft_strequ(path, cur->file) == 1)
		{
			ret = ft_strdup(cur->path);
			ft_hash_cmd_add(ret, path, 1);
			return (ret);
		}
		cur = cur->next;
	}
	return (NULL);
}

int			ft_parse_cmd(char *str, int len)
{
	char *cmd;

	(void)len;
	if ((str) && ((str[0] == ';') || (str[0] == '&')))
	{
		ft_print_msg(": parse error near ", str);
		return (1);
	}
	if (!(str) || str[0] == '\0' || ft_test_andor() == 0)
		return (0);
	if (!(g_job && g_and_or_line))
		ft_set_job_str(str, len);
	cmd = ft_strndup(str, (size_t)len);
	if (ft_parser_go(cmd, str) == 1)
	{
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}

t_quoteflag	*ft_init_parse_init(void)
{
	t_quoteflag	*f;

	g_job_start = NULL;
	g_job_end = 0;
	g_and_or_line = 0;
	g_skip = 0;
	if (g_subst == 0)
		g_job = 0;
	f = ft_get_quoteflag();
	ft_ini_quoteflag_spl(f);
	f->i = -1;
	return (f);
}

int			ft_free_qf(t_quoteflag *f)
{
	free(f);
	return (1);
}
