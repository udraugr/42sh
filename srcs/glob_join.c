/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:39:53 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 16:36:32 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*globbing_join_quote_special(char *name, int extra)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	if (!(ret = ft_memalloc(len + extra + 1)))
		exit(1);
	while (name[i])
	{
		if (ft_strchr("\\\'\"", name[i]))
			ret[j++] = '\\';
		ret[j++] = name[i++];
	}
	return (ret);
}

static void	globbing_join_get_newname(char **new_name, char *name)
{
	char	*ret;
	int		i;
	int		extra;

	i = -1;
	extra = 0;
	while (name[++i])
		if (ft_strchr("\\\'\"", name[i]))
			extra++;
	if (!extra)
		if (!(ret = ft_strdup(name)))
			exit(1);
	if (extra)
		ret = globbing_join_quote_special(name, extra);
	*new_name = ret;
}

char		*glob_join(char *path, char *name)
{
	char	*new_name;
	char	*ret;

	globbing_join_get_newname(&new_name, name);
	if (!(ret = ft_strjoin(path, new_name)))
		exit(1);
	ft_strdel(&new_name);
	return (ret);
}
