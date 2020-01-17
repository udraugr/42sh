/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:26:37 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/12 14:20:04 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_type_alias_print(char *av, char *tmp)
{
	ft_putstr(av);
	ft_putstr(" is aliased to '");
	ft_putstr(tmp);
	ft_putstr("'\n");
}

static void		ft_type_bin_print(char *av, char *tmp)
{
	ft_putstr(av);
	ft_putstr(" is ");
	ft_putendl(tmp);
}

static void		ft_type_builtin_print(char *av)
{
	ft_putstr(av);
	ft_putstr(" is a shell builtin\n");
}

static void		ft_type_error_print(char *av)
{
	ft_print_msg(": type: not found ", av);
	g_built_rc = 1;
	ft_set_shell("?", "1");
}

int				ft_type(char **av)
{
	int			i;
	char		*tmp;
	char		*all_alias;

	i = 0;
	tmp = NULL;
	while (av && av[++i])
	{
		ft_set_shell("?", "0");
		if ((all_alias = ft_read_alias())
			&& (tmp = take_value_alias(all_alias, av[i])) != NULL)
			ft_type_alias_print(av[i], tmp);
		else if (ft_test_built_in(av[i]) == 1)
			ft_type_builtin_print(av[i]);
		else if (!(tmp = ft_get_file_path(av[i], g_envi->first_list)))
			ft_type_error_print(av[i]);
		else
			ft_type_bin_print(av[i], tmp);
		ft_strdel(&tmp);
		ft_strdel(&all_alias);
	}
	return (1);
}
