/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:58:38 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 21:00:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_print_msg(char *s, char *name)
{
	char *tmp;

	tmp = ft_strdup("");
	tmp = ft_strfjoin(tmp, g_app_name);
	tmp = ft_strfjoin(tmp, s);
	tmp = ft_strfjoin(tmp, name);
	tmp = ft_strfjoin(tmp, "\n");
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return (-1);
}

int		ft_is_dir(char *path)
{
	struct stat	buf;
	int			i;

	if ((i = lstat(path, &buf)) == 0)
	{
		if (S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode) ||
			S_ISREG(buf.st_mode))
			return (1);
	}
	return (0);
}

int		ft_check_dir(char *find_path)
{
	ft_set_shell("?", "1");
	if ((access(find_path, F_OK)) == -1)
	{
		ft_print_msg(" : no such file or directory: ", find_path);
		g_built_rc = 1;
		return (-1);
	}
	else if ((access(find_path, X_OK)) == -1)
	{
		ft_print_msg(" : permission denied: ", find_path);
		g_built_rc = 1;
		return (-1);
	}
	if (!(ft_is_dir(find_path)))
	{
		ft_print_msg(" : not a directory: ", find_path);
		g_built_rc = 1;
		return (-1);
	}
	ft_set_shell("?", "0");
	return (0);
}

void	ft_del_quotes(char **args)
{
	int i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			args[i] = ft_clear_quotes(args[i]);
			i++;
		}
	}
}

void	exit_shell(void)
{
	exit(1);
}
