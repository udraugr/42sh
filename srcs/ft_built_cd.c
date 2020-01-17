/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:10:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 20:54:43 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_get_p_dir(char *path)
{
	struct stat	buf;
	char		*tmp;
	int			i;

	if ((i = lstat(path, &buf)) == 0)
	{
		if (S_ISLNK(buf.st_mode))
		{
			if ((tmp = malloc(sizeof(char) * 502)))
			{
				tmp[0] = '/';
				tmp[1] = '\0';
				if ((i = readlink(path, tmp + 1, 500)) != -1)
				{
					free(path);
					path = tmp;
				}
			}
		}
	}
	return (path);
}

void		ft_cd(char *path2, int flag, char **locals)
{
	char *tmp;
	char *full;
	char *p;

	p = ft_strdup(path2);
	tmp = ft_get_lpwd(locals);
	if ((p = ft_tst_cdpath(p)) && (ft_check_dir(p) == 0) && (chdir(p) == 0))
	{
		if (!(full = ft_strnew(255)))
			exit_shell(1);
		getcwd(full, 255);
		if (flag == 0 && p[0] == '/')
			ft_set_shell("PWD", p);
		else
			ft_set_shell("PWD", full);
		ft_set_shell("OLDPWD", tmp);
		free(full);
	}
	free(p);
	free(tmp);
}

int			ft_cd_flag(char *str, int *flag)
{
	int i;
	int	f1;

	i = 1;
	f1 = 0;
	if (str[0] != '-' || ((str[0] == '-') && str[1] == '\0'))
		return (1);
	while (str[i])
	{
		if (str[i] == 'L')
			f1 = 0;
		else if (str[i] == 'P')
			f1 = 1;
		else
			return (1);
		i++;
	}
	*flag = f1;
	return (0);
}

char		*ft_cd_setpath(char *str, char **locals)
{
	char	*tmp;

	if (!(str) || (str && ft_strequ(str, "+")))
	{
		if ((tmp = ft_get_env2("HOME", locals)))
			return (tmp);
		return (ft_get_env("HOME"));
	}
	else if (str && (ft_strequ(str, "-")))
	{
		if ((tmp = ft_get_env2("OLDPWD", locals)))
			return (tmp);
		return (ft_get_env("OLDPWD"));
	}
	else
		return (ft_strdup(str));
}

int			ft_built_cd(char **av, char **locals)
{
	char	*s;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (av[++i])
	{
		if ((ft_cd_flag(av[i], &flag) == 1))
		{
			if ((av[i + 1]) && av[i + 1][0] != '\0' && ((g_built_rc = 1)))
			{
				ft_print_msg(" :cd :", " too many arguments");
				ft_set_shell("?", "1");
				return (1);
			}
			else
				break ;
		}
	}
	s = ft_cd_setpath(av[i], locals);
	ft_cd(s, flag, locals);
	if (s)
		free(s);
	return (1);
}
