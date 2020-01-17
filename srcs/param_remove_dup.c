/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_remove_dup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 20:29:35 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parm_remlarge_inloop(int i, int l, char *save, char *val)
{
	if (i < l)
	{
		*save = *val;
		*val = 0;
	}
	else
		*save = '\0';
}

char	*param_remlarge(char *val, char *pat)
{
	char	save;
	int		i;
	int		pos;
	int		l;

	i = -1;
	save = '\0';
	l = ft_strlen(val);
	pos = -1;
	while (val[++i])
	{
		parm_remlarge_inloop(i, l, &save, &val[i + 1]);
		if (glob_check(val, pat, 0, 0))
			pos = i;
		if (save)
			val[i + 1] = save;
	}
	if (pos > -1)
	{
		if (pos < l)
			ft_memmove(val, &val[pos + 1], ft_strlen(&val[pos]));
		else
			val[0] = '\0';
	}
	return (val);
}
