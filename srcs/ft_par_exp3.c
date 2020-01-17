/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/19 12:39:01 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_val_min(char *s, int j, char *tmp, char **val)
{
	if (!(*val = ft_get_env(tmp)) && ft_strchr("-=?", s[j + 1]))
	{
		if ((*val = ft_strdup(s + j + 2)) && ft_repl_parm_sub(val) == 1)
		{
			free(*val);
			free(tmp);
			return (1);
		}
		if (s[j + 1] == '=' && tmp && ft_strlen(tmp) > 0)
			ft_set_shell(tmp, *val);
		else if (s[j + 1] == '=' && (!tmp || ft_strlen(tmp) == 0))
		{
			free(tmp);
			free(*val);
			ft_print_badsub(s, 1, tmp);
			return (1);
		}
		else if (s[j + 1] == '?' && (*val)[0] == '\0')
		{
			free(*val);
			ft_print_badsub(s, 1, tmp);
			return (1);
		}
	}
	return (0);
}

int		ft_get_val_plus(char *s, int j, char *tmp, char **val)
{
	if (s[j + 1] == '+' && *val)
	{
		free(*val);
		if (tmp && ft_strlen(tmp) > 0)
		{
			free(tmp);
			*val = ft_strdup(s + j + 2);
			if (ft_repl_parm_sub(val) == 1)
			{
				free(*val);
				return (1);
			}
		}
		else
		{
			g_subs_rc = 1;
			ft_print_msg(": parameter not exist: ", s);
			ft_set_shell("?", "1");
			free(tmp);
			return (1);
		}
	}
	else
		free(tmp);
	return (0);
}

char	*ft_get_val_rr(char *s, int j, char *tmp)
{
	char	*flag;
	char	*val;
	char	*tmp2;

	tmp2 = NULL;
	if (s[j + 1] == '#' && (j = j + 1))
		flag = ft_strdup("##");
	else
		flag = ft_strdup("#");
	if ((val = ft_get_env(tmp)))
	{
		tmp2 = ft_strnew(ft_strlen(s) - j + 1);
		tmp2 = ft_strcat(tmp2, s + j + 1);
		val = param_rem(val, flag, tmp2);
	}
	else
		val = ft_strdup("");
	free(flag);
	if (tmp2)
		free(tmp2);
	return (val);
}

int		ft_check_parm_unrec(char *s, int j)
{
	char	*tmp;

	if (s[j + 1] && !(ft_strchr("-=?+", s[j + 1])))
	{
		tmp = ft_strndup(s + j + 1, 1);
		ft_print_msg(": unrecognized modifier: `", tmp);
		free(tmp);
		ft_set_shell("?", "1");
		s[0] = '\0';
		g_subs_rc = 1;
		return (1);
	}
	return (0);
}
