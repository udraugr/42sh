/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:37:25 by wveta             #+#    #+#             */
/*   Updated: 2019/08/29 15:49:41 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*commands_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;

	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (g_cmd->cmd_list[i] && (name = g_cmd->cmd_list[i]))
	{
		i++;
		if (ft_strncmp(name, text, len) == 0)
			return (ft_strdup(name));
	}
	return ((char *)NULL);
}

char	*rl_gets(char *pr)
{
	char *line_read;

	line_read = NULL;
	g_input = NULL;
	line_read = read_line(pr);
	free(pr);
	return (line_read);
}

char	*ft_get_file(char *path)
{
	char	*s;
	int		i;
	int		l;

	s = NULL;
	l = ft_strlen(path);
	i = l - 1;
	while (i >= 0 && path[i] != '/')
		i--;
	if (i > 0)
	{
		s = ft_alloc_char(l - i + 1);
		s[0] = '\0';
		s = ft_strcat(s, path + i + 1);
	}
	return (s);
}
