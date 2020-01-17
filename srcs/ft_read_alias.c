/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:54 by udraugr-          #+#    #+#             */
/*   Updated: 2019/11/12 13:05:09 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char			*ft_error_terminate(char *error_mesage,
								int open_fd, char **str_for_free)
{
	ft_print_msg(": Take_alias: ", error_mesage);
	if (open_fd != -1)
		close(open_fd);
	if (str_for_free)
		ft_strdel(str_for_free);
	return (NULL);
}

char				*ft_read_alias(void)
{
	char			*all_alias;
	char			*file;
	char			buffer[4096];
	int				fd;
	int				read_bytes;

	file = ft_strfjoin(ft_get_env("HOME"), "/.alias_42");
	fd = open(file, O_CREAT | O_RDONLY, 0644);
	ft_strdel(&file);
	if (fd == -1)
		return (ft_error_terminate("Can't open alias file!", -1, 0));
	if ((all_alias = ft_strnew(0)) == NULL)
		return (ft_error_terminate("Malloc can't allocate memory!", fd, 0));
	while ((read_bytes = read(fd, buffer, 4095)) > 0)
	{
		buffer[read_bytes] = '\0';
		if ((all_alias = ft_strfjoin(all_alias, buffer)) == NULL)
			return (ft_error_terminate("Malloc can't allocate memory!",
						fd, 0));
	}
	close(fd);
	if (read_bytes == -1)
		return (ft_error_terminate("Can't read the alias!", 1, &all_alias));
	return (all_alias);
}
