/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/11 14:24:23 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_val_prc(char *s, int j, char *tmp)
{
	char	*flag;
	char	*val;
	char	*tmp2;

	tmp2 = NULL;
	if (s[j + 1] == '%' && (j = j + 1))
		flag = ft_strdup("%%");
	else
		flag = ft_strdup("%");
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

char	*ft_get_parm_start(char *s, int k, int *j)
{
	char	*tmp;

	if ((*j = ft_subst_lbr(s + k + 2)) == -1)
		*j = ft_strlen(s + k + 2);
	tmp = ft_alloc_char(*j + 1);
	tmp[*j] = '\0';
	tmp = ft_strncpy(tmp, s + k + 2, *j);
	return (tmp);
}

char	*ft_do_parm_subs(char *tmp, int *n)
{
	while (tmp[++(*n)] && ft_check_ekran(tmp, *n) == 0)
	{
		if (tmp[*n] == '#' && *n == 0 && (*n = -7))
		{
			tmp = ft_get_parm_ll(tmp);
			break ;
		}
		else if (tmp[*n] == ':' && (*n = -7))
		{
			tmp = ft_get_parm_qq(tmp);
			break ;
		}
		else if (tmp[*n] == '#' && (*n = -7))
		{
			tmp = ft_get_parm_rr(tmp);
			break ;
		}
		else if (tmp[*n] == '%' && (*n = -7))
		{
			tmp = ft_get_parm_prc(tmp);
			break ;
		}
	}
	return (tmp);
}

char	*ft_repl_parm_norm(char *val, int jj)
{
	char	*tmp2;
	int		k;

	tmp2 = ft_strdup(val + jj);
	k = 0;
	tmp2 = ft_repl_subs(tmp2, &k, ft_strlen(tmp2));
	val[jj] = '\0';
	val = ft_strfjoin(val, tmp2);
	free(tmp2);
	return (val);
}

int		ft_repl_parm_sub(char **val)
{
	int		jj;

	jj = 0;
	while (jj < (int)ft_strlen((*val)))
	{
		if ((*val)[jj] == '$' && (ft_check_ekran((*val), jj)) == 0 &&
			(*val)[jj + 1] && (*val)[jj + 1] == '{')
		{
			(*val) = ft_repl_parm_norm((*val), jj);
			if (g_subs_rc == 1)
			{
				ft_set_shell("?", "1");
				if (g_subshell == 0)
					return (1);
				else
					exit_shell(1);
			}
		}
		jj++;
	}
	return (0);
}
