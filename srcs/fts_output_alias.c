/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_output_alias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:41:05 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 19:08:55 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void					ft_output_alias(char *all_alias, char *av,
										int flag_alias, int *ret)
{
	char				*ans;
	int					i;

	if ((ans = ft_find_alias(all_alias, av)) == NULL)
	{
		ft_print_msg(": alias: alias not found: ", av);
		ft_set_shell("?", "1");
		*ret = 0;
	}
	else
	{
		if (flag_alias)
			ft_putstr("alias ");
		i = 1;
		while (ans[i] && ans[i] != -10)
			++i;
		write(1, &ans[1], i - 1);
		write(1, "\n", 1);
	}
}

void					print_all_alias(char *all_alias, int flag_alias)
{
	char				**arr_alias;
	int					i;

	arr_alias = ft_strsplit(all_alias, -10);
	i = -1;
	while (arr_alias[++i])
	{
		if (flag_alias == 1)
			ft_putstr("alias ");
		write(1, arr_alias[i], ft_strlen(arr_alias[i]));
		ft_putchar('\n');
		ft_strdel(&arr_alias[i]);
	}
	free(arr_alias);
	arr_alias = 0;
}
