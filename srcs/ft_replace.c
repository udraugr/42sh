/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 21:49:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_repl_til_flag(int *flag, int j, char *s, int code)
{
	if (*flag == 1)
		s = ft_repl_tilda(s, j);
	if (code == 1)
		*flag = 0;
	return (s);
}

char	*ft_replays_t(char *s, int j)
{
	char	*tmp;

	if (s[j] == '~' && ft_check_ekran(s, j) == 0 && j > 0 &&
		s[j - 1] == '=')
	{
		tmp = ft_strdup(s + j);
		tmp = ft_repl_tilda(tmp, ft_strlen(tmp));
		s[j] = '\0';
		s = ft_strfjoin(s, tmp);
		free(tmp);
	}
	return (s);
}

char	*ft_repl_parm(char *s, int flag, int len)
{
	int		j;
	char	q;
	int		k;

	j = -1;
	q = ' ';
	while (++j < len && ((k = ft_repl_check(s, len, &q, j)) > -777))
	{
		if (k == 1 || (k == -1 && ((j = j - 1) > -777)))
			continue;
		if (q == ' ' && flag == 1)
			s = ft_repl_end_til(s, j, &flag);
		else if (q != '\'' && s[j] == '$' && (k != 2) && s[j + 1] &&
		(ft_strchr("_?{", s[j + 1]) || ft_isalpha(s[j + 1])) &&
		ft_check_ekran(s, j) == 0 && (s = ft_repl_parm_n(s, &flag, &j)))
		{
			if (g_subs_rc != 0)
				return (s);
		}
		else
			s = ft_replays_t(s, j);
		len = ft_strlen(s);
	}
	s = ft_repl_til_flag(&flag, j, s, 0);
	return (s);
}

int		ft_repl_sym(char *s, int j)
{
	int		i;

	i = 1;
	while (s[j + i])
	{
		if ((i == 1 && ft_isdigit(s[j + i])) ||
			(!ft_isalnum(s[j + i]) && !ft_strchr("?_", s[j + i])))
			break ;
		i++;
	}
	return (i);
}

char	**ft_cmd_replays(char **str)
{
	char	**ret;
	int		i;

	ret = NULL;
	g_subs_rc = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_replays(str[i]);
			i++;
		}
		str = ft_press_matr(str);
		if (!str[0])
		{
			g_subs_rc = 1;
			ft_print_msg(": command not found ", " ");
			ft_set_shell("?", "1");
			if (g_subshell != 0)
				exit_shell(1);
		}
		return (str);
	}
	return (ret);
}
