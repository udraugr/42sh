/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_cmd_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/12/12 17:16:46 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clear_one_hash(t_listh *tmp)
{
	if (tmp->file)
		free(tmp->file);
	if (tmp->path)
		free(tmp->path);
	free(tmp);
}

void	ft_hash_all_del(char *str)
{
	t_listh	*cur;
	t_listh	*prev;
	t_listh	*tmp;

	prev = NULL;
	tmp = NULL;
	cur = g_envi->hash_first;
	while (cur)
	{
		if ((!(str) || ft_strcmp(str, cur->file) == 0))
		{
			tmp = cur;
			if (prev)
				prev->next = cur->next;
			else
				g_envi->hash_first = cur->next;
			cur = cur->next;
			ft_clear_one_hash(tmp);
			continue;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_print_code3(t_listh *tmp)
{
	ft_putstr("builtin hash -p ");
	ft_putstr(tmp->path);
	ft_putstr(" ");
	ft_putstr(tmp->file);
}

void	ft_print_one(char *av, int code)
{
	t_listh	*tmp;

	tmp = g_envi->hash_first;
	while (tmp)
	{
		if (((av) && ft_strcmp(tmp->file, av) == 0) || (code == 3 && !(av)))
		{
			if (code == 1)
				ft_putstr(tmp->path);
			else if (code == 2)
			{
				ft_putstr(tmp->file);
				write(STDOUT_FILENO, "          ", 10 - ft_strlen(tmp->file));
				ft_putstr(tmp->path);
			}
			else if (code == 3)
				ft_print_code3(tmp);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}
