/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:38:04 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 19:08:33 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			ft_not_found(char *alias_name)
{
	ft_print_msg(": unalias: alias not found: ", alias_name);
}

char				*ft_del_alias(char *alias_str, char *alias)
{
	char			*find_alias;
	char			*alias_end;
	char			*new_str;
	int				len;

	find_alias = ft_find_alias(alias_str, alias);
	alias_end = find_alias + 1;
	while (*alias_end && *alias_end != -10)
		++alias_end;
	if (*alias_end)
		++alias_end;
	len = ft_strlen(alias_str) - (alias_end - find_alias);
	new_str = ft_strnew(len);
	ft_strncpy(new_str, alias_str, find_alias - alias_str);
	ft_strcpy(&new_str[find_alias - alias_str], alias_end);
	ft_strdel(&alias_str);
	return (new_str);
}

static void			ft_action(char **all_alias, char *av_str, int *ret)
{
	if ((ft_find_alias(*all_alias, av_str)) == 0)
	{
		ft_not_found(av_str);
		*ret = 0;
	}
	else
		*all_alias = ft_del_alias(*all_alias, av_str);
}

static int			unalias(char **av)
{
	char			*all_alias;
	int				len;
	int				ret;
	int				flag_del_all;
	int				i;

	if ((len = ft_arr_len(av)) < 2)
	{
		ft_print_msg(": unalias:", " usage: unalias -a name [name ...]");
		return (0);
	}
	if ((all_alias = ft_read_alias()) == NULL)
		return (0);
	ret = 1;
	flag_del_all = 0;
	i = 0;
	while (++i < len && ft_strcmp("-a", av[i]) == 0)
		flag_del_all = 1;
	i -= 1;
	while (++i < len)
		ft_action(&all_alias, av[i], &ret);
	(flag_del_all == 1) ? ft_change_alias(0) : ft_change_alias(all_alias);
	ft_strdel(&all_alias);
	return (ret);
}

int					ft_unalias(char **av)
{
	int				ans;

	ans = unalias(av);
	if (ans == 0)
		ft_set_shell("?", "1");
	else
		ft_set_shell("?", "0");
	return (1);
}
