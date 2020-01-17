/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/12/23 11:36:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_exp_name(char *str, int j)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) || str[i] == '?' || str[i] == '_')
	{
		while (str[++i] && i < j)
		{
			if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) ||
				(str[i] == '_')))
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_unset_env_parm(char *str)
{
	int i;

	i = 0;
	if ((i = ft_get_ind_env(str, g_envi->env)) != -1)
	{
		free(g_envi->env[i]);
		while (g_envi->env[i])
		{
			g_envi->env[i] = g_envi->env[i + 1];
			i++;
		}
	}
}

char	**ft_put_locals(char **av)
{
	int i;

	i = 0;
	if (av)
	{
		while (av && av[i])
		{
			ft_go_export(av[i], 1);
			free(av[i]);
			i++;
		}
		free(av);
	}
	ft_set_shell("?", "0");
	return (NULL);
}

int		ft_test_andor(void)
{
	int rc;

	rc = 1;
	if (g_and_or == 1 && g_not == 0 && g_rc != 0)
		rc = 0;
	else if (g_and_or == 1 && g_not == 1 && g_rc == 0)
		rc = 0;
	else if (g_and_or == 2 && g_not == 0 && g_rc == 0)
		rc = 0;
	else if (g_and_or == 2 && g_not == 1 && g_rc != 0)
		rc = 0;
	g_not = 0;
	g_and_or = 0;
	return (rc);
}

int		ft_shell_put_test(char *str)
{
	char	*tmp;
	int		j;
	int		i;

	if (!(tmp = ft_strchr(str, '=')))
		return (0);
	else
	{
		j = tmp - str;
		i = 0;
		while (g_shell && g_shell[i])
		{
			if (ft_strncmp(g_shell[i], str, j + 1) == 0 &&
				((ft_test_put_env(str)) == 1))
			{
				free(g_shell[i]);
				g_shell[i] = ft_strdup(str);
				str[0] = '\0';
				return (1);
			}
			i++;
		}
		return (0);
	}
}
