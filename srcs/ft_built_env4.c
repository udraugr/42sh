/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/12/02 18:30:27 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_printenv(char **av)
{
	int		i;
	char	*tmp;

	i = 1;
	if (av && av[i])
	{
		if (av[i][0] == '-')
		{
			ft_print_msg(": usage: printenv [name], error: ", av[1]);
			ft_set_shell("?", "1");
			g_built_rc = 1;
			return (1);
		}
		else if ((tmp = ft_get_env(av[i])))
		{
			ft_putstr(tmp);
			free(tmp);
			return (1);
		}
	}
	ft_print_env();
	ft_set_shell("?", "0");
	return (1);
}

char	*ft_cre_parm_str(char *parm, char *value)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * (2 + ft_strlen(parm) +
	ft_strlen(value)))))
		exit_shell(1);
	str[0] = '\0';
	str = ft_strcat(str, parm);
	str = ft_strcat(str, "=");
	str = ft_strcat(str, value);
	return (str);
}
