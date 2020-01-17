/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 20:38:39 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*param_remlarge_rev(char *var, char *pat)
{
	int		i;
	int		pos;

	pos = -1;
	i = ft_strlen(var) - 1;
	while (i > -1)
	{
		if (glob_check(&var[i], pat, 0, 0))
			pos = i;
		i--;
	}
	if (pos > -1)
		var[pos] = 0;
	return (var);
}

static char	*param_remsmall_rev(char *var, char *pat)
{
	int		i;

	i = ft_strlen(var) - 1;
	while (i > -1)
	{
		if (glob_check(&var[i], pat, 0, 0))
		{
			var[i] = 0;
			break ;
		}
		i--;
	}
	return (var);
}

static void	param_setval(char save, char *val)
{
	if (save)
		*val = save;
}

static char	*param_remsmall(char *val, char *pat)
{
	char	save;
	int		i;
	int		l;

	i = -1;
	save = '\0';
	l = ft_strlen(val);
	while (val[++i])
	{
		parm_remlarge_inloop(i, l - 1, &save, &val[i + 1]);
		if (glob_check(val, pat, 0, 0))
		{
			if (i < l)
			{
				param_setval(save, &val[i + 1]);
				val = ft_strcpy(val, val + i + 1);
			}
			else
				val[0] = '\0';
			break ;
		}
		param_setval(save, &val[i + 1]);
	}
	return (val);
}

char		*param_rem(char *val, char *flag, char *pat)
{
	if (!val || !*val || !flag || !*flag)
		return (NULL);
	if (!pat || !*pat)
		return (val);
	if (ft_strequ(flag, "#"))
		return (param_remsmall(val, pat));
	if (ft_strequ(flag, "##"))
		return (param_remlarge(val, pat));
	if (ft_strequ(flag, "%"))
		return (param_remsmall_rev(val, pat));
	if (ft_strequ(flag, "%%"))
		return (param_remlarge_rev(val, pat));
	return (NULL);
}
