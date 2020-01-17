/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:06:43 by thaley            #+#    #+#             */
/*   Updated: 2019/12/25 13:58:38 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char		*calc_path(char *s)
{
	char	*tmp;

	tmp = ft_get_env("PWD");
	g_input->autocompl.key_check = 2;
	if (ft_strncmp(s, "./", 2) == 0)
		tmp = ft_strfjoin(tmp, s + 1);
	else if (s[0] != '.' && s[0] != '/')
	{
		tmp = ft_strfjoin(tmp, "/");
		tmp = ft_strfjoin(tmp, s);
	}
	else
		g_input->autocompl.key_check = 1;
	if (ft_strncmp(s, "../", 2) == 0)
	{
		tmp = ft_path_level_up(tmp);
		tmp = ft_strfjoin(tmp, s + 2);
		g_input->autocompl.key_check = 2;
	}
	return (tmp);
}

char		*find_tail(char *str)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = ft_strlen(str) - 1;
	if (str[i] == '/')
		return (ret);
	while (i > -1)
	{
		if (str[i] == '/' && str[i + 1])
		{
			ret = ft_strdup(str + i + 1);
			str[i + 1] = '\0';
			return (ret);
		}
		i--;
	}
	return (ret);
}

char		*take_path(char *key)
{
	int		i;
	int		count;
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	i = -1;
	count = 0;
	while (key[++i])
		key[i] == '/' ? count++ : 0;
	ret = ft_get_env("PWD");
	tmp = ft_strfjoin(ret, "/");
	i = ft_strlen(key);
	if (i > 0 && key[i - 1] == '/')
		i--;
	i += ft_strlen(tmp);
	ret = ft_strnjoin(tmp, key, i);
	ft_free(tmp);
	tmp = NULL;
	return (ret);
}

void		home_dir(char *tmp)
{
	char	*temp;

	temp = NULL;
	temp = ft_get_env("HOME");
	g_input->autocompl.path = ft_strjoin(temp, tmp + 1);
	ft_free(temp);
	temp = NULL;
	g_input->autocompl.key_check = 2;
}

char		*parse_path(char *tmp)
{
	char	*tail;

	tail = find_tail(tmp);
	if (tmp[0] == '~')
		home_dir(tmp);
	else if (tmp[0] == '.')
		g_input->autocompl.path = calc_path(tmp);
	else if (tmp[0] != '/')
	{
		if (!tail)
			g_input->autocompl.path = ft_get_env("PWD");
		else
			g_input->autocompl.path = take_path(tmp);
	}
	if (!tail && g_input->autocompl.key_check < 2 && tmp[0] != '/')
		tail = ft_strdup(tmp);
	if (!g_input->autocompl.path)
		g_input->autocompl.path = ft_strdup(tmp);
	count_file_match(tail);
	find_match(tail);
	return (tail);
}
