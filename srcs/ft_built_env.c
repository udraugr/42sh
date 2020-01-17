/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/12/26 16:09:23 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_env2(char *parm, char **shell)
{
	int		i;
	int		j;

	if (shell)
	{
		i = 0;
		j = ft_strlen(parm);
		while (shell[i])
		{
			if (ft_strnequ(parm, shell[i], j) == 1 &&
			shell[i][j] == '=')
				return (ft_replays(ft_strdup(shell[i] + j + 1)));
			i++;
		}
	}
	return (NULL);
}

char	**ft_set_shell(char *parm, char *value)
{
	int		i;
	char	*str;

	if (!(value) || !(parm))
		return (NULL);
	if (ft_strcmp(parm, "?") == 0)
	{
		g_rc = 1;
		if (ft_strcmp(value, "0") == 0)
			g_rc = 0;
	}
	str = ft_cre_parm_str(parm, value);
	if ((i = ft_get_ind_env(parm, g_shell)) == -1)
		g_shell = ft_add_shell(str, g_shell);
	else
	{
		free(g_shell[i]);
		g_shell[i] = str;
	}
	ft_test_put_env(str);
	if ((i = ft_strequ(parm, "PATH")) == 1)
		ft_reset_cmd_list();
	return (NULL);
}

int		ft_unset_env(char **parm)
{
	int i;
	int j;

	j = 0;
	while (parm && parm[++j])
	{
		if ((i = ft_get_ind_env(parm[j], g_envi->env)) != -1)
		{
			free(g_envi->env[i]);
			while (g_envi->env[i])
			{
				g_envi->env[i] = g_envi->env[i + 1];
				i++;
			}
		}
		ft_unset_shell(parm[j]);
	}
	return (1);
}

char	**ft_add_shell(char *str, char **shell)
{
	int		i;
	char	**s;

	i = ft_calc_matr_rows(shell);
	i = i + 2;
	if (!(s = (char **)malloc(sizeof(char *) * (i))))
		exit_shell();
	i = 0;
	while (shell[i])
	{
		s[i] = shell[i];
		i++;
	}
	s[i] = str;
	s[i + 1] = NULL;
	free(shell);
	return (s);
}

char	*ft_get_env(char *parm)
{
	char	*ret;

	ret = NULL;
	ret = ft_get_env2(parm, g_shell);
	return (ret);
}
