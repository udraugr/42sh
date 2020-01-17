/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ekran.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 21:00:17 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/26 19:57:14 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	telo_cicla(char *old_str, int *i, int *dquote, int *squote)
{
	if (old_str[*i] == '\\' && !(*squote))
	{
		ft_memmove(&old_str[*i], &old_str[*i + 1], ft_strlen(&old_str[*i]));
		(*i)++;
	}
	else if (old_str[*i] == '\'' && !(*dquote))
	{
		ft_memmove(&old_str[*i], &old_str[*i + 1], ft_strlen(&old_str[*i]));
		*squote ^= 1;
	}
	else if (old_str[*i] == '"' && !(*squote))
	{
		ft_memmove(&old_str[*i], &old_str[*i + 1], ft_strlen(&old_str[*i]));
		*dquote ^= 1;
	}
	else
		++(*i);
}

char		*del_ekran(char *old_str)
{
	int		squote;
	int		dquote;
	int		i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (old_str[i])
		telo_cicla(old_str, &i, &dquote, &squote);
	return (old_str);
}
