/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:05:14 by thaley            #+#    #+#             */
/*   Updated: 2019/12/08 01:00:44 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*search_key_loop(int *i, int curs)
{
	char	*tmp;

	tmp = NULL;
	while ((*i) > 0 && g_input->input[(*i) - 1] > 32)
	{
		(*i)--;
		if ((*i) == 0 || ((*i) > 0 && g_input->input[(*i) - 1] < 33))
		{
			tmp = ft_strsub(g_input->input, (*i), curs - (*i));
			while (--(*i) > -1)
			{
				if (g_input->input[(*i)] > 32)
					g_input->autocompl.file = 1;
			}
			if (tmp[0] == '/' || tmp[0] == '~' || (tmp[0] == '.' && tmp[1] &&\
				tmp[1] == '.') || (tmp[0] == '.' && tmp[1] && tmp[1] == '/'))
				g_input->autocompl.file = 1;
			else if ((*i) == -1 && !g_input->autocompl.file)
				g_input->autocompl.cmd = 1;
			break ;
		}
	}
	return (tmp);
}

char	*if_tmp_null(int *i, int curs)
{
	char	*tmp;

	tmp = NULL;
	while ((*i) > 0 && g_input->input[(*i)] < 33)
		(*i)--;
	if ((*i) > 0 && ((*i) + 1) != curs)
		g_input->autocompl.file = 1;
	else if ((*i) == 0 && g_input->input[(*i)] < 33)
		g_input->autocompl.cmd = 1;
	else if ((*i) == 0 && g_input->input[(*i)] > 32)
	{
		g_input->autocompl.cmd = 1;
		tmp = ft_strsub(g_input->input, 0, 1);
	}
	return (tmp);
}

char	*still_not_find(int i)
{
	char	*tmp;

	tmp = NULL;
	if (i == 0 && g_input->input[i] < 33)
	{
		g_input->autocompl.cmd = 1;
		return (NULL);
	}
	else if (i == 0 && g_input->input[i] > 32)
	{
		tmp = ft_strsub(g_input->input, 0, 1);
		if (tmp[0] == '/' || tmp[0] == '~' || (tmp[0] == '.' && tmp[1] &&\
			tmp[1] == '.') || (tmp[0] == '.' && tmp[1] && tmp[1] == '/'))
			g_input->autocompl.file = 1;
		else
			g_input->autocompl.cmd = 1;
	}
	return (tmp);
}

char	*find_key(int curs)
{
	char	*tmp;
	int		i;

	i = curs;
	tmp = NULL;
	if (i > 0)
	{
		tmp = search_key_loop(&i, curs);
		if (!tmp && i > 0)
			tmp = if_tmp_null(&i, curs);
	}
	if (g_input->autocompl.cmd == 0 && g_input->autocompl.file == 0)
		tmp = still_not_find(i);
	return (tmp);
}
