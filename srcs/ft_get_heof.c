/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 10:41:47 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/27 10:54:47 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*heof_return(t_cmdlist *cmd, int i, int j)
{
	int			j1;
	char		*heof;

	j1 = 0;
	if (cmd->avcmd[i + 1] &&
	(heof = ft_get_sufx_name(cmd->avcmd[i + 1], &j1, 0)))
	{
		cmd->avcmd[i + 1][j1] = '\0';
		cmd->avcmd[i][j] = '\0';
	}
	else
	{
		ft_print_msg(" : parse error ", cmd->avcmd[i]);
		return (NULL);
	}
	return (heof);
}

char			*ft_get_heof(char *ind, t_cmdlist *cmd, int i, int j)
{
	char		*heof;
	int			j1;

	(void)ind;
	if ((int)ft_strlen(cmd->avcmd[i]) - 2 > j)
	{
		if (ft_isalnum(cmd->avcmd[i][j + 2]) != 1 &&
		ft_print_msg(" : parse error ", cmd->avcmd[i]) == -1)
			return (NULL);
		j1 = j;
		heof = ft_get_sufx_name(cmd->avcmd[i], &j1, j + 2);
		cmd->avcmd[i][j1] = '\0';
	}
	else
	{
		heof = heof_return(cmd, i, j);
		if (!heof)
			return (NULL);
	}
	if (ft_test_file_mame(heof) != 0 && ft_free_ret(heof))
		return (NULL);
	return (heof);
}
