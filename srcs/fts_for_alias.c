/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_for_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:40:26 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 09:42:45 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					ft_arr_len(char **av)
{
	int			len;

	len = 0;
	while (av && av[len])
		++len;
	return (len);
}

void				ft_change_alias(char *new_alias)
{
	int				len;
	int				fd;
	char			*tmp;

	tmp = ft_get_env("HOME");
	tmp = ft_strfjoin(tmp, "/.alias_42");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(tmp);
	len = ft_strlen(new_alias);
	if (fd == -1)
		ft_print_msg("'Open' cant read the file!", "");
	else
		write(fd, new_alias, len);
}

char				*ft_find_alias(char *str, char *alias)
{
	char			*tmp;
	char			*ans;
	int				len_alias;

	len_alias = ft_strlen(alias);
	tmp = ft_strnew(1 + len_alias + 1);
	tmp[0] = -10;
	ft_strncpy(&tmp[1], alias, len_alias);
	tmp[len_alias + 1] = '=';
	ans = ft_strstr(str, tmp);
	ft_strdel(&tmp);
	return (ans);
}
