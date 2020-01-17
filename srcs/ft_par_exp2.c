/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/24 20:58:57 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parname_loop_n(int *i, int *j, char *str)
{
	if ((*i == 0 &&
	(!ft_isalpha(str[*j])) && (!ft_strchr("_?", str[*j]))) ||
	(*i > 0 &&
	(ft_strchr(" ", str[*j]) ||
	(!(ft_isalnum(str[*j]) || ft_strchr("_?", str[*j]))))))
		return (1);
	return (0);
}

int		ft_parname_loop(int *f_sub, int *i, int *j, char *str)
{
	if (*f_sub == 1)
	{
		if (ft_strchr("}:#%", str[*j]) && (ft_check_ekran(str, *j)) == 0)
		{
			if (*j > 0)
				*f_sub = 0;
			else
				return (1);
		}
		else if (ft_strchr("$", str[*j]) && ft_check_ekran(str, *j) == 0)
			return (1);
		else if (ft_parname_loop_n(i, j, str) == 1)
			return (1);
		(*i)++;
	}
	else
	{
		if (str[*j] == '$' && ft_check_ekran(str, *j) == 0 &&
		str[*j + 1] && str[*j + 1] == '{' && (*f_sub = 1))
		{
			*i = 0;
			(*j)++;
		}
	}
	return (0);
}

int		ft_test_parname(char *str)
{
	int i;
	int j;
	int	f_sub;

	i = 0;
	j = -1;
	f_sub = 1;
	while (str && str[++j])
	{
		if (ft_parname_loop(&f_sub, &i, &j, str) == 1)
			return (1);
	}
	return (0);
}

char	*ft_print_badsub(char *s, int i, char *tmp)
{
	g_subs_rc = 1;
	if (i == 0)
		ft_print_msg(": bad substitution : ", s);
	else if (i == 1)
	{
		ft_print_msg(": parameter null or not set: ", tmp);
		free(tmp);
	}
	ft_set_shell("?", "1");
	if (g_subshell != 0)
		exit_shell(1);
	return (s);
}

int		ft_subst_lbr(char *s)
{
	int i;
	int nbr;

	i = -1;
	nbr = 1;
	while (s && s[++i])
	{
		if (s[i] == '{' && ft_check_ekran(s, i) == 0)
			nbr++;
		else if (s[i] == '}' && ft_check_ekran(s, i) == 0)
		{
			nbr--;
			if (nbr == 0)
				return (i);
		}
	}
	return (-1);
}
