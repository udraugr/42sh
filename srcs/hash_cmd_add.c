/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_cmd_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 23:28:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_hash_cmd_add(char *path, char *name, int num)
{
	t_listh *tmp;

	tmp = g_envi->hash_first;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->file) == 0 && (tmp->path))
		{
			free(tmp->path);
			tmp->path = ft_strdup(path);
			return ;
		}
		tmp = tmp->next;
	}
	if (!(tmp = malloc(sizeof(t_listh))))
		exit_shell();
	tmp->file = ft_strdup(name);
	tmp->path = ft_strdup(path);
	tmp->hash = hashly(name);
	tmp->hashcount = num;
	tmp->next = g_envi->hash_first;
	g_envi->hash_first = tmp;
}

int		ft_hash_usage(char *av)
{
	ft_set_shell("?", "1");
	ft_print_msg(": hash: invalid option: ", av);
	ft_print_msg(": usage: hash [-lr] [-p pathname] [-dt] [name ...]", " ");
	return (1);
}

char	*ft_get_hash_path(char *path)
{
	t_listh			*cur;
	char			*ret;
	unsigned int	hash;

	if (!(path))
		return (NULL);
	hash = hashly(path);
	cur = g_envi->hash_first;
	while (cur)
	{
		if (hash == cur->hash && ft_strequ(path, cur->file) == 1)
		{
			ret = ft_strdup(cur->path);
			cur->hashcount++;
			return (ret);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	ft_set_andor(int i, t_quoteflag *f)
{
	f->i_cmd = f->i_cmd + f->i + 2;
	f->i = -1;
	g_and_or = i;
}
