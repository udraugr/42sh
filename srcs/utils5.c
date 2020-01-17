/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:17:22 by wveta             #+#    #+#             */
/*   Updated: 2019/09/10 20:52:22 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_print_env(void)
{
	int i;

	i = 0;
	while (g_shell[i])
	{
		ft_putstr(g_shell[i]);
		ft_putstr("\n");
		i++;
	}
	return (1);
}

int		ft_tst_tilda(char *s, int j)
{
	char	*tmp;

	tmp = ft_alloc_char(j + 1);
	tmp[0] = '\0';
	tmp = ft_strncpy(tmp, s, j);
	tmp[j] = '\0';
	tmp = ft_tilda_path(tmp);
	ft_putstrf(tmp);
	if (ft_is_dir(tmp))
		return (1);
	return (0);
}

char	*ft_get_usr_tilda(char *path)
{
	char	*tmp;
	char	*home;

	if ((tmp = ft_strchr(path, '/')) != NULL)
	{
		home = ft_get_home(path, (tmp - path));
		if (home)
			home = ft_strfjoin(home, tmp);
	}
	else
		home = ft_get_home(path, ft_strlen(path));
	return (home);
}

int		ft_tst_end_til(char *s, int j, int *flag)
{
	if (ft_strchr("!#%:", s[j]) && *flag == 1)
	{
		if (ft_tst_tilda(s, j) == 1)
		{
			*flag = 0;
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}

void	ft_putstrf(char *s)
{
	if (s != NULL)
	{
		ft_putstr(s);
		free(s);
	}
}
