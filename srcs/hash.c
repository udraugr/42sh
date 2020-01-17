/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/12/12 16:47:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hashly(char *str)
{
	unsigned int hash;

	hash = 0;
	while (str && (*str))
	{
		hash = (hash * 1664525) + (unsigned char)(*str) + 1013904223;
		str++;
	}
	return (hash);
}

char			*ft_tilda_znak(char *s, int j, int type)
{
	char	*tmp;
	char	*tmp2;

	if (type == 0)
		tmp = ft_get_env("PWD");
	else
		tmp = ft_get_env("OLDPWD");
	if (!(tmp))
	{
		if (!(tmp = ft_strnew(500)))
			exit_shell();
		getcwd(tmp, 255);
	}
	tmp2 = ft_alloc_char(ft_strlen(s) + ft_strlen(tmp) - 1);
	tmp2[0] = '\0';
	tmp2 = ft_strcat(tmp2, tmp);
	tmp2 = ft_strcat(tmp2, s + j + 2);
	free(s);
	free(tmp);
	return (tmp2);
}

char			*ft_replays(char *str)
{
	int		flag;

	if (!(str))
		return (str);
	flag = 0;
	if (str[0] == '~' && (ft_strlen(str) == 1))
	{
		free(str);
		return (ft_get_env("HOME"));
	}
	else if (str[0] == '~' && ft_strlen(str) > 1)
		flag = 1;
	return (ft_repl_parm(str, flag, ft_strlen(str)));
}

char			*ft_repl_tilda(char *s, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_alloc_char(j + 1);
	tmp[0] = '\0';
	tmp = ft_strncpy(tmp, s, j);
	tmp[j] = '\0';
	tmp = ft_tilda_path(tmp);
	if (*(s + j) != '\0')
	{
		tmp2 = ft_alloc_char(ft_strlen(s) + ft_strlen(tmp) + 1);
		tmp2[0] = '\0';
		tmp2 = ft_strcat(tmp2, tmp);
		free(tmp);
		tmp2 = ft_strcat(tmp2, s + j);
		free(s);
		return (tmp2);
	}
	free(s);
	return (tmp);
}

char			*ft_repl_end_til(char *s, int j, int *flag)
{
	if (ft_strchr("!#%@\"\'^*()=\\.:", s[j]) && *flag == 1)
	{
		s = ft_repl_tilda(s, j - 1);
		*flag = 0;
	}
	else if (s[j] == '+')
		s = ft_tilda_znak(s, j - 1, 0);
	else if (s[j] == '-')
		s = ft_tilda_znak(s, j - 1, 1);
	return (s);
}
