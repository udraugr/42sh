/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repl_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 23:45:50 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_repl_parm_n(char *s, int *flag, int *j)
{
	s = ft_repl_til_flag(flag, *j, s, 1);
	s = ft_repl_env(s, j);
	(*j)--;
	return (s);
}

int		ft_repl_check_end(char *s, char *q, int j)
{
	if (*q == ' ' && (s[j] == '\'' || s[j] == '"'))
	{
		*q = s[j];
		return (1);
	}
	else if (*q != ' ' && (s[j] == *q))
	{
		*q = ' ';
		return (1);
	}
	else if (s[j] == '\\' && *q != '\'')
	{
		return (1);
	}
	return (0);
}

int		ft_repl_check(char *s, int len, char *q, int j)
{
	if (*q == '\'')
	{
		if (s[j] == '\'')
		{
			*q = ' ';
			return (1);
		}
		return (1);
	}
	else if (s[j] == '\\' && j + 1 < len && (s[j + 1] == '\''
		|| s[j + 1] == '"' || s[j + 1] == '\\'))
	{
		return (1);
	}
	else
		return (ft_repl_check_end(s, q, j));
}

int		ft_free_ret(char *s)
{
	ft_free(s);
	return (1);
}
