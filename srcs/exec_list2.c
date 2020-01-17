/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:00:14 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 17:34:45 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_set_var_ex_lst(int *j, int *l)
{
	char	*ret;

	ret = ft_get_env("PATH");
	*j = 0;
	*l = 0;
	return (ret);
}

int		ft_test_cmd_file(t_cmdlist *cur_cmd)
{
	struct stat	buff;
	int			k;

	if (!(cur_cmd->find_path))
		return (-1);
	if (ft_check_file(cur_cmd->find_path, X_OK) != 0)
		return (-1);
	if ((k = stat(cur_cmd->find_path, &buff)) == 0 &&
		(buff.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_print_msg(" : is a directory: ", cur_cmd->find_path);
		ft_set_shell("?", "1");
		return (-1);
	}
	return (0);
}

void	ft_add_built_to_list(int j)
{
	g_cmd->cmd_list[j] = ft_strdup("exit");
	g_cmd->cmd_list[j + 1] = ft_strdup("export");
	g_cmd->cmd_list[j + 2] = ft_strdup("unset");
	g_cmd->cmd_list[j + 3] = ft_strdup("set");
	g_cmd->cmd_list[j + 4] = NULL;
}
