/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_full_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 13:35:39 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_path_level_up(char *tmp)
{
	int i;

	i = ft_strlen(tmp) - 1;
	while (i > -1)
	{
		if (tmp[i] == '/')
			break ;
		i--;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_calc_full_path(char *s)
{
	char	*tmp;

	if (s[0] == '/')
		return (s);
	tmp = ft_get_env("PWD");
	if (ft_strncmp(s, "./", 2) == 0)
		tmp = ft_strfjoin(tmp, s + 1);
	else if (s[0] != '.' && s[0] != '/')
	{
		tmp = ft_strfjoin(tmp, "/");
		tmp = ft_strfjoin(tmp, s);
	}
	if (ft_strncmp(s, "../", 2) == 0)
	{
		tmp = ft_path_level_up(tmp);
		tmp = ft_strfjoin(tmp, s + 2);
	}
	free(s);
	s = tmp;
	return (s);
}

char	*ft_calc_in_calc(char *s)
{
	char	**ret;

	if (!s)
		return (s);
	if (!(ret = (char **)malloc(sizeof(char *) * 2)))
		exit(1);
	ret[0] = ft_strdup(s);
	ret[1] = NULL;
	ret = ft_all_calc_tst(ret);
	free(s);
	s = ft_strdup(ret[0]);
	ft_free_char_matr(ret);
	return (s);
}
