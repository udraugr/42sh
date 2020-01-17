/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 10:10:19 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/12 16:44:13 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			ft_globbing_addline(char *line, t_list **alist)
{
	t_list	*list;

	if (!(list = ft_memalloc(sizeof(t_list))))
		exit(1);
	list->content = ft_strdup(line);
	list->next = 0;
	ft_lstadd_last(alist, list);
}

bool			ft_globbing_split(char *line, char **path, char **pat)
{
	size_t	i;
	int		len;

	i = -1;
	len = -1;
	*path = 0;
	*pat = 0;
	while (line[++i])
		if (line[i] == '/')
			len = i;
	if (!line[len + 1])
		return (false);
	if (len != -1)
		if (!(*path = ft_strndup(line, len + 1)))
			exit(1);
	if (!(*pat = ft_strdup(line + len + 1)))
		exit(1);
	return (true);
}

t_list			*ft_globbing_path_cycle(DIR *dir, char *path, char *pat)
{
	t_dir	*entry;
	t_list	*list;
	char	*join_line;

	list = 0;
	while ((entry = readdir(dir)))
	{
		if (pat[0] != '.' && entry->d_name[0] == '.')
			continue ;
		if (ft_strcmp(entry->d_name, "..") &&\
				ft_strcmp(entry->d_name, ".") &&\
				glob_check(entry->d_name, pat, 0, 0))
		{
			if (!(join_line = glob_join(path, entry->d_name)))
				exit(1);
			ft_globbing_addline(join_line, &list);
			free(join_line);
		}
	}
	if (list)
		ft_lst_sort(&list, &ft_strcmp);
	return (list);
}
