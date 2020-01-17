/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:16:11 by thaley            #+#    #+#             */
/*   Updated: 2019/12/18 16:23:09 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		count_file_match(char *key)
{
	struct dirent	*dn;
	DIR				*dir;

	dir = NULL;
	if (!(dir = opendir(g_input->autocompl.path)))
		return ;
	while ((dn = readdir(dir)))
	{
		if (ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			if (key && !ft_strncmp(dn->d_name, key, ft_strlen(key)))
				g_input->autocompl.amount++;
			else if (!key)
				g_input->autocompl.amount++;
		}
	}
	g_input->autocompl.seach_res = (char **)malloc(sizeof(char *)\
								* (g_input->autocompl.amount + 1));
	g_input->autocompl.seach_res[g_input->autocompl.amount] = 0;
	closedir(dir);
}

void		find_match(char *key)
{
	struct dirent	*dn;
	DIR				*dir;
	int				i;

	i = 0;
	if (!(dir = opendir(g_input->autocompl.path)))
		return ;
	while ((dn = readdir(dir)))
	{
		if (ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			if (key && !ft_strncmp(dn->d_name, key, ft_strlen(key)))
				g_input->autocompl.seach_res[i++] = ft_strdup(dn->d_name);
			else if (!key)
				g_input->autocompl.seach_res[i++] = ft_strdup(dn->d_name);
		}
	}
	closedir(dir);
	g_input->autocompl.seach_res[g_input->autocompl.amount] = NULL;
}

void		all_files_in_path(void)
{
	DIR				*dir;
	struct dirent	*dn;
	int				i;

	i = 0;
	dir = NULL;
	count_file_match(NULL);
	if (!(dir = opendir(g_input->autocompl.path)))
		return ;
	while ((dn = readdir(dir)))
	{
		if (dn->d_name[0] != '\0' && ft_strlen(dn->d_name) > 0 &&
			ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, ".."))
		{
			g_input->autocompl.seach_res[i] = ft_strdup(dn->d_name);
			i++;
		}
	}
	closedir(dir);
}

void		for_print(char **str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		if (g_input->autocompl.max_len < len)
			g_input->autocompl.max_len = len;
		i++;
	}
	g_input->autocompl.max_len += 2;
	g_input->autocompl.num_in_row = g_input->ws.ws_col\
	/ g_input->autocompl.max_len;
	g_input->autocompl.col_pos = (g_input->autocompl.amount\
	/ g_input->autocompl.num_in_row) + 1;
}

void		find_file(char *key)
{
	char			*tmp;

	tmp = NULL;
	if (g_input->autocompl.tab_count < 2)
	{
		if (!key)
		{
			g_input->autocompl.path = ft_get_env("PWD");
			all_files_in_path();
		}
		else
			tmp = parse_path(key);
	}
	if (g_input->autocompl.amount > 1 && g_input->autocompl.tab_count == 2)
	{
		ascii_sort(g_input->autocompl.seach_res);
		for_print(g_input->autocompl.seach_res);
		print_array(g_input->autocompl.seach_res);
	}
	else if (g_input->autocompl.amount == 1)
		change_input(g_input->autocompl.seach_res, tmp);
	else if (g_input->autocompl.amount == 0)
		g_input->autocompl.tab_count = 0;
	ft_free(tmp);
	tmp = NULL;
}
