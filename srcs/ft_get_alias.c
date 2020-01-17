/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 10:57:37 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/18 17:29:03 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char					*take_value_alias(char *all_alias, char *alias_name)
{
	char				*value;
	char				*tmp;
	int					i;

	tmp = ft_find_alias(all_alias, alias_name);
	if (tmp == NULL)
		return (0);
	tmp += 1 + ft_strlen(alias_name) + 2;
	i = 0;
	while (tmp[i] && tmp[i] != -10)
		++i;
	if (tmp[i - 1] == '"')
		--i;
	if ((value = ft_strndup(tmp, i)) == NULL)
		ft_print_msg(": ft_get_alias:", " Malloc can't allocate the memory!");
	return (value);
}

static char				**ft_add_arr(char **new, char **ret, int i_repl)
{
	char				**result;
	int					len_new;
	int					len_ret;
	int					i;
	int					j;

	len_new = ft_arr_len(new);
	len_ret = ft_arr_len(ret);
	result = 0;
	if ((result = (char **)malloc(sizeof(char *) *
							(len_new + (len_ret - 1) + 1))) == NULL)
		ft_print_msg(": ft_add_arr:", " Malloc can't allocate the memory!");
	else
	{
		i = -1;
		while (++i < i_repl)
			result[i] = ft_strdup(ret[i]);
		j = -1;
		while (new[++j])
			result[i++] = ft_strdup(new[j]);
		while (ret[++i_repl])
			result[i++] = ft_strdup(ret[i_repl]);
		result[i] = 0;
	}
	return (result);
}

static void				ft_del_arr(char ***arr)
{
	int32_t				i;

	i = -1;
	while ((*arr)[++i])
	{
		ft_strdel(&(*arr)[i]);
	}
	free(*arr);
	arr = 0;
}

static char				**ft_prep_for_add_arr(char **ans, char **av, int i)
{
	char				**tmp;
	char				**new;

	new = ft_split_pipes(ans[0]);
	ft_strdel(ans);
	if (new == NULL)
	{
		ft_print_msg(": ft_get_alias:",
				" Malloc can't allocate the memory!");
		return (0);
	}
	tmp = ft_add_arr(new, av, i);
	ft_del_arr(&new);
	return (tmp);
}

char					**ft_get_alias(char **av, int i)
{
	char				**tmp;
	char				*ans;
	char				*all_alias;
	char				*first;

	if (av[i] && ft_strlen(av[i]) == 0)
		return (av);
	all_alias = ft_read_alias();
	first = ft_strdup(av[i]);
	while (all_alias && (ans = take_value_alias(all_alias, av[i])) != NULL)
	{
		tmp = ft_prep_for_add_arr(&ans, av, i);
		if (tmp == NULL)
			break ;
		ft_del_arr(&av);
		av = tmp;
		if (ft_strequ(av[i], first) == 1)
			break ;
	}
	ft_strdel(&first);
	ft_strdel(&all_alias);
	return (av);
}
