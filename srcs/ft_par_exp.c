/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/19 12:32:40 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_parm_ll(char *tmp)
{
	char	*val;

	ft_strcpy(tmp, tmp + 1);
	if (ft_test_parname(tmp))
		return (tmp = ft_print_badsub(tmp, 0, NULL));
	if ((val = ft_get_env(tmp)))
	{
		tmp[0] = '\0';
		tmp = ft_putfnbr(ft_strlen(val), tmp);
	}
	else
	{
		tmp = ft_print_badsub(tmp, 0, NULL);
		tmp[0] = 0;
	}
	return (tmp);
}

char	*ft_get_parm_qq(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (((j = ft_strchr(s, ':') - s)) > -1)
	{
		if (ft_check_parm_unrec(s, j))
			return (s);
		tmp = ft_strndup(s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		if (ft_get_val_min(s, j, tmp, &val) == 1)
			return (s);
		if (ft_get_val_plus(s, j, tmp, &val) == 1)
			return (s);
		free(s);
		if (!(val))
			val = ft_strdup("");
		return (val);
	}
	return (s);
}

char	*ft_get_parm_rr(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (ft_repl_parm_sub(&s) != 1 && ((j = ft_strchr(s, '#') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		val = ft_get_val_rr(s, j, tmp);
		free(tmp);
		free(s);
		return (val);
	}
	return (s);
}

char	*ft_get_parm_prc(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (ft_repl_parm_sub(&s) != 1 && ((j = ft_strchr(s, '%') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (ft_test_parname(tmp))
		{
			free(tmp);
			return (s = ft_print_badsub(s, 0, NULL));
		}
		val = ft_get_val_prc(s, j, tmp);
		free(tmp);
		free(s);
		return (val);
	}
	return (s);
}

char	*ft_repl_subs(char *s, int *k, int i)
{
	char	*tmp;
	char	*ret;
	int		j;
	int		n;

	if (ft_test_parname(s + *k + 2))
		return (s = ft_print_badsub(s, 0, NULL));
	tmp = ft_get_parm_start(s, *k, &j);
	n = -1;
	tmp = ft_do_parm_subs(tmp, &n);
	if (n != -7)
	{
		if (ft_test_sub(s + *k + 2, i - 2) == 1)
			return (s);
		tmp = ft_get_parm_simple(tmp);
	}
	ret = ft_alloc_char(*(k) + ft_strlen(tmp) + ft_strlen(s) + 1);
	ret[0] = '\0';
	ret = ft_strncat(ret, s, *(k));
	ret = ft_strcat(ret, tmp);
	if ((int)ft_strlen(s) > *k + 2 + j + 1)
		ret = ft_strcat(ret, s + *k + 2 + j + 1);
	free(tmp);
	free(s);
	return (ret);
}
