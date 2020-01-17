/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:00:14 by wveta             #+#    #+#             */
/*   Updated: 2019/12/10 19:07:54 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char				*ft_push_alias(char *all_alias, char *av)
{
	char				*ans;
	int					len_all_alias;
	int					len_ans;
	int					i;

	ans = 0;
	len_all_alias = ft_strlen(all_alias);
	len_ans = len_all_alias + 1 + ft_strlen(av) + 2 + 1 + 1;
	if ((ans = ft_strnew(len_ans)) == NULL)
		return (0);
	ft_strcpy(ans, all_alias);
	ans[len_all_alias++] = -10;
	i = 0;
	while (len_all_alias < len_ans)
	{
		ans[len_all_alias++] = av[i++];
		if (ans[len_all_alias - 1] == '=')
			break ;
	}
	ans[len_all_alias++] = '"';
	ft_strcpy(&ans[len_all_alias], &av[i]);
	ans[len_ans - 3] = '"';
	ans[len_ans - 2] = -10;
	return (ans);
}

static char				*ft_replace_alias(char *all_alias,
								char *av, char *alias_name)
{
	char				*ans;
	char				*tmp;

	ans = ft_del_alias(ft_strdup(all_alias), alias_name);
	tmp = ft_push_alias(ans, av);
	ft_strdel(&ans);
	ans = tmp;
	return (ans);
}

static char				*ft_add_alias(char *all_alias, char *av)
{
	char				*ans;
	char				*alias_name;
	int					len_av;
	int					len_alias_name;

	len_av = ft_strlen(av);
	ans = 0;
	len_alias_name = ft_strchr(av, '=') - av;
	if ((alias_name = ft_strnew(len_alias_name)) != NULL)
	{
		ft_strncpy(alias_name, av, len_alias_name);
		if (ft_find_alias(all_alias, alias_name) != NULL)
			ans = ft_replace_alias(all_alias, av, alias_name);
		else
			ans = ft_push_alias(all_alias, av);
		ft_strdel(&alias_name);
	}
	if (ans == NULL)
	{
		ft_print_msg("alias:", " Malloc can't alloacte memory!");
		ft_set_shell("?", "1");
	}
	ft_strdel(&all_alias);
	return (ans);
}

static int				ft_action(char **all_alias, char *av_str,
										int flag_alias, int *ret)
{
	if (ft_strchr(av_str, '=') == NULL)
		ft_output_alias(*all_alias, av_str, flag_alias, ret);
	else
	{
		if ((*all_alias = ft_add_alias(*all_alias, av_str)) == NULL)
			return (1);
	}
	return (0);
}

int						ft_alias(char **av)
{
	int					i;
	char				*all_alias;
	int					flag_alias;
	int					ret;

	if ((all_alias = ft_read_alias()) == NULL && (!(ft_set_shell("?", "1"))))
		return (1);
	ret = 1;
	flag_alias = 0;
	i = 0;
	while (av[++i] && ft_strcmp("-p", av[i]) == 0)
		flag_alias = 1;
	if (ft_arr_len(&av[i]) < 1)
		print_all_alias(all_alias, flag_alias);
	else
	{
		--i;
		while (av[++i])
			if (ft_action(&all_alias, av[i], flag_alias, &ret) == 1)
				break ;
	}
	ft_change_alias(all_alias);
	ft_strdel(&all_alias);
	return (1);
}
