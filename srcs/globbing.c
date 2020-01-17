/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:10:19 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/24 13:39:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			del_str(void *content, size_t size)
{
	ft_memdel(&content);
	(void)size;
}

int				ft_globbing_getdir(char *path, DIR **dir)
{
	if (!path)
		if (!(*dir = opendir(".")))
			return (0);
	if (path && *path)
		if (!(*dir = opendir(path)))
			return (0);
	return (1);
}

static void		ft_globbing_cycle(char *line, t_list **alist)
{
	DIR			*dir;
	t_list		*list;
	char		*path;
	char		*pat;

	if (!ft_globbing_split(line, &path, &pat))
		return (ft_globbing_addline(line, alist));
	if (!ft_globbing_getdir(path, &dir))
		ft_globbing_addline(line, alist);
	else
	{
		if ((list = ft_globbing_path_cycle(dir, path, pat)))
			ft_lstadd_last(alist, list);
		else
			ft_globbing_addline(line, alist);
	}
	if (dir)
		closedir(dir);
	if (path)
		ft_strdel(&path);
	if (pat)
		ft_strdel(&pat);
}

void			ft_globbing_listtoline(t_list *list, char ***table)
{
	char		**ret;
	int			i;

	i = ft_lstsize(list);
	if (!(ret = ft_memalloc(sizeof(char*) * (i + 1))))
		exit(1);
	i = -1;
	while (list)
	{
		if (!(ret[++i] = ft_strdup(list->content)))
			exit(1);
		list = list->next;
	}
	*table = ret;
}

char			**ft_globbing(char **table)
{
	t_list		*list;
	int			i;
	char		**ret;

	if (!table || !*table)
		return (0);
	i = -1;
	list = 0;
	while (table[++i])
		ft_globbing_cycle(table[i], &list);
	ft_free_table(&table);
	ft_globbing_listtoline(list, &ret);
	ft_lstdel(&list, &del_str);
	return (ret);
}
