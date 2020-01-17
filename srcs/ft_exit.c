/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:00:25 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/12 15:04:25 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exit_error(char *mess, char *input)
{
	ft_print_msg(mess, input);
	ft_set_shell("?", "1");
	g_built_rc = 1;
}

int			ft_exit(char **av)
{
	int		rc;
	char	*str;

	rc = 0;
	if (av && av[1] && av[2])
	{
		ft_exit_error(" : exit: too many arguments", " ");
		return (1);
	}
	else if (av && av[1])
	{
		str = av[1];
		while (str && *str != '\0')
		{
			if (!(ft_isdigit(*str) && ((rc = rc * 10 + (*str - 48)) >= 0)))
			{
				ft_exit_error(" : exit: numeric argument required: ", av[1]);
				return (1);
			}
			str++;
		}
	}
	ft_final_free();
	exit(rc);
	return (rc);
}
