/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 04:45:51 by thaley            #+#    #+#             */
/*   Updated: 2019/12/23 19:39:27 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		count_cmd_match(char *key)
{
	int		i;

	i = 0;
	while (g_cmd->cmd_list[i])
	{
		if (key && !ft_strncmp(g_cmd->cmd_list[i], key, ft_strlen(key)))
			g_input->autocompl.amount++;
		i++;
	}
	if (g_input->autocompl.amount > 0)
	{
		g_input->autocompl.seach_res = (char **)malloc(sizeof(char *)\
								* (g_input->autocompl.amount + 1));
		g_input->autocompl.seach_res[g_input->autocompl.amount] = 0;
	}
	else
		g_input->autocompl.seach_res = NULL;
}

void		find_cmd(char *key)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (g_input->autocompl.tab_count < 2)
	{
		count_cmd_match(key);
		while (g_cmd->cmd_list[i])
		{
			if (key && !ft_strncmp(g_cmd->cmd_list[i], key, ft_strlen(key)))
				g_input->autocompl.seach_res\
				[j++] = ft_strdup(g_cmd->cmd_list[i]);
			i++;
		}
	}
	if (g_input->autocompl.amount > 1 && g_input->autocompl.tab_count == 2)
	{
		for_print(g_input->autocompl.seach_res);
		print_array(g_input->autocompl.seach_res);
	}
	else if (g_input->autocompl.amount == 1)
		change_input(g_input->autocompl.seach_res, key);
}
