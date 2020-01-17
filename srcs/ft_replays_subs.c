/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replays_subs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/27 16:17:22 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_ret_subs(char *str, int i)
{
	char *tmp;

	tmp = ft_alloc_char(i + 4);
	tmp[0] = '\0';
	tmp = ft_strncat(tmp, str - 2, i + 3);
	ft_print_msg(": bad substitution: ", tmp);
	free(tmp);
	g_subs_rc = 1;
	ft_set_shell("?", "1");
	return (1);
}

int		ft_test_sub(char *str, int i)
{
	int j;
	int	fl;

	j = 0;
	fl = 0;
	if (i > 0)
	{
		while (j <= i && str[j])
		{
			if (fl == 0 && str[j] == '}')
				fl = 1;
			else if (fl == 0 && (ft_strchr("!@\"\'^()\\.$", str[j])))
				return (ft_ret_subs(str, i));
			else if (fl == 1 && str[j] == '$' && ft_check_ekran(str, j) == 0
			&& str[j + 1] && str[j + 1] == '{')
				fl = 0;
			j++;
		}
		return (0);
	}
	return (ft_ret_subs(str, i));
}

char	*ft_get_parm_simple(char *tmp)
{
	char	*val;

	if (!(val = ft_get_env(tmp)))
		val = ft_strdup("");
	free(tmp);
	return (val);
}

char	*ft_get_norm_tmp(char *s, int *k, char *val, int i)
{
	char *tmp;

	if (*k > 0)
	{
		tmp = ft_strndup(s, *k);
		tmp = ft_strfjoin(tmp, val);
	}
	else
		tmp = ft_strdup(val);
	tmp = ft_strfjoin(tmp, s + *k + i);
	return (tmp);
}

char	*ft_repl_env(char *s, int *k)
{
	int		i;
	char	*tmp;
	char	*val;

	if (s[*k + 1] == '{' && (i = ft_strlen(s + *k) - 1))
		return (ft_repl_subs(s, k, i));
	if (!(s[*k + 1] == '_' || ft_isalpha(s[*k + 1]) || s[*k + 1] == '?'))
		return (s);
	i = ft_repl_sym(s, *k);
	tmp = ft_strndup(s + *k + 1, i - 1);
	if ((val = ft_get_env(tmp)))
	{
		free(tmp);
		tmp = ft_get_norm_tmp(s, k, val, i);
		free(val);
		free(s);
		return (tmp);
	}
	else
		s[*k] = '\0';
	free(tmp);
	return (s);
}
