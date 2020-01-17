/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 14:58:38 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 13:08:47 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_tst_env(char *s, int j)
{
	int		i;
	char	*tmp;
	char	*val;

	i = ft_repl_sym(s, j);
	tmp = ft_alloc_char(i);
	tmp = ft_strncpy(tmp, s + j + 1, i - 1);
	tmp[i] = '\0';
	if ((val = ft_get_env(tmp)))
	{
		ft_putstr(val);
		free(val);
	}
	free(tmp);
	return (i + j);
}

int		ft_tst_home(char *s, int len)
{
	char	*path;

	path = NULL;
	if ((path = ft_get_home(s, len)) != NULL)
		ft_putstr(path);
	free(path);
	return (0);
}

char	*ft_get_home(char *s, int len)
{
	char			*uname;
	struct passwd	*pwd;
	char			*home;

	uname = ft_strnew((size_t)len);
	uname[0] = '\0';
	uname = ft_strncat(uname, s + 1, (size_t)(len - 1));
	pwd = getpwnam(uname);
	free(uname);
	if (!(pwd))
		return (NULL);
	else
		return (home = strdup(pwd->pw_dir));
}

char	*ft_get_my_home(void)
{
	struct passwd	*pw;
	uid_t			uid;
	char			*home;

	home = ft_get_env("HOME");
	if (home)
		return (home);
	home = NULL;
	uid = geteuid();
	pw = getpwuid(uid);
	if (pw)
	{
		home = ft_strdup(pw->pw_dir);
	}
	return (home);
}

void	ft_reset_cmd_list(void)
{
	ft_free_list();
	g_cmd->cmd_list = ft_free_char_matr(g_cmd->cmd_list);
	g_envi->first_list = ft_create_exe_list();
}
