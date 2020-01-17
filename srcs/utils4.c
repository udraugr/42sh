/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:52:00 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 16:35:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_list(t_listf *list)
{
	t_listf	*cur;
	int		count;

	count = 0;
	cur = list;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	*ft_set_dirpath(int lpath, char *paths)
{
	char *path;

	if (!(path = (char *)malloc(sizeof(char) * (lpath + 1))))
		exit_shell();
	path[0] = '\0';
	path = ft_strncpy(path, (const char *)paths, (size_t)lpath);
	path[lpath] = '\0';
	return (path);
}

char	*ft_set_full_exe(char *d_name, char *path, char *full)
{
	full = ft_strcpy(full, path);
	full = ft_strcat(full, "/");
	full = ft_strcat(full, d_name);
	return (full);
}

char	*ft_alloc_char(int l)
{
	char *tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * l)))
		exit_shell();
	tmp[l - 1] = '\0';
	return (tmp);
}

char	*ft_tilda_path(char *path)
{
	char *tmp;
	char *home;

	if (path[0] == '~')
	{
		if ((ft_strlen(path) > 1) && (path[1] != '/')
			&& (home = ft_get_usr_tilda(path)) != NULL)
		{
			free(path);
			return (home);
		}
		else if ((ft_strlen(path) == 1 || path[1] == '/') &&
			((home = ft_get_my_home()) != NULL))
		{
			tmp = ft_strnew((size_t)(ft_strlen(path) + ft_strlen(home)));
			tmp[0] = '\0';
			tmp = ft_strcat(tmp, home);
			tmp = ft_strcat(tmp, path + 1);
			free(path);
			free(home);
			return (tmp);
		}
	}
	return (path);
}
