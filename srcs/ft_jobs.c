/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/17 22:08:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_set_job_str(char *start, int end)
{
	g_job_start = start;
	g_job_end = end;
	return (1);
}

int			ft_ampers_test(char *str, int i, int start)
{
	if (str[i + start] == '&' &&
		(i + start == 0 || (i + start >= 1 && str[i + start - 1] != '&')
		|| (i + start >= 2 && str[i + start - 2] == '\\')) &&
		str[i + start + 1] != '&' &&
		(str[i + start - 1] != '<') && (str[i + start - 1] != '>') &&
		(str[i + start + 1] != '<') && (str[i + start + 1] != '>') &&
		(i + start == 0 || str[i + start - 1] != '\\'))
		return (1);
	return (0);
}

char		**ft_get_sub_av(void)
{
	char	**ret;

	ret = NULL;
	if ((ret = (char **)malloc(sizeof(char *) * 5)))
	{
		ret[4] = NULL;
		ret[0] = ft_strdup("echo");
		ret[1] = ft_strdup(g_job_start);
		ret[1][g_job_end] = '\0';
		ret[2] = ft_strdup("|");
		ret[3] = ft_strdup(g_app_full_name);
	}
	return (ret);
}

void		ft_locals_to_env(char **locals)
{
	int		i;
	char	*parm;
	char	*val;
	int		j;

	i = 0;
	while (locals && locals[i])
	{
		if ((val = ft_strchr(locals[i], '=')) &&
				((j = val - locals[i]) > 0))
		{
			parm = ft_strdup(locals[i]);
			parm[j] = '\0';
			val = ft_strdup(locals[i] + j + 1);
			ft_exp_env(parm, val);
		}
		i++;
	}
}

char		*ft_get_shell_str(char *in, int len)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if ((tmp = malloc(sizeof(char) * (len + 1))))
	{
		tmp[0] = '\0';
		tmp = ft_strncpy(tmp, in, len);
		tmp[len] = '\0';
		ret = ft_strdup("echo '");
		ret = ft_strfjoin(ret, tmp);
		free(tmp);
		ret = ft_strfjoin(ret, "' | ");
		ret = ft_strfjoin(ret, g_app_full_name);
	}
	return (ret);
}
