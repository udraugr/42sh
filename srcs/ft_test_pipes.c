/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:43:20 by wveta             #+#    #+#             */
/*   Updated: 2019/12/05 13:38:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_test_pipe(char **av, int start)
{
	int j;

	j = start;
	while (av && av[j])
	{
		if (av[0][0] == '(' || av[0][0] == '{')
			return (2);
		if (ft_strequ(av[j], "|") == 1 && av[j][0] != '"' && av[j][0] != '\'')
			return (j);
		j++;
	}
	return (0);
}

int		ft_get_count_in_pipe(char **av, int start)
{
	int count;
	int j;
	int i;

	j = 0;
	count = 0;
	while (av && av[j])
		j++;
	j--;
	if (j >= start)
	{
		if (av)
		{
			i = start;
			while (av[i] && av[i] != NULL && i <= j)
			{
				if (ft_strequ(av[i], "|") == 1)
					return (count);
				i++;
				count++;
			}
		}
	}
	return (count);
}

char	*ft_opt_color(char *av, char *ret, int *j)
{
	*j = 1;
	if (ft_strcmp(av, "ls") == 0)
		ret = ft_strdup("-G");
	else
		ret = ft_strdup("--color");
	return (ret);
}

char	**ft_get_pipe_av(char **av, int start)
{
	char	**ret;
	int		count;
	int		i;
	int		j;

	ret = NULL;
	count = ft_get_count_in_pipe(av, start);
	if (count > 0 &&
	(!(ret = (char **)malloc(sizeof(char *) * (count + 2)))))
		exit_shell();
	j = 0;
	ret[count] = NULL;
	ret[count + 1] = NULL;
	i = start;
	while (av[i] && i < count + start)
	{
		ret[i - start + j] = ft_strdup(av[i]);
		if ((ft_strcmp(av[i], "ls") == 0 || ft_strcmp(av[i], "grep") == 0)
			&& g_color == 1 && (j == 0) && i - start == 0)
			ret[i - start + j] = ft_opt_color(av[i], ret[i - start + j], &j);
		i++;
	}
	ret = ft_press_matr(ret);
	return (ret);
}

int		ft_test_args(char *args)
{
	int i;

	i = 0;
	if (args && args)
	{
		while (args[i])
		{
			if (ft_isspace(args[i]))
				i++;
			else if ((ft_strncmp(args + i, "|", 1) == 0 ||
					ft_strncmp(args + i, "||", 2) == 0 ||
					ft_strncmp(args + i, "&", 1) == 0 ||
					ft_strncmp(args + i, "&&", 2) == 0))
			{
				ft_print_msg(": parse error near: ", args + i);
				return (0);
			}
			else
				return (1);
		}
	}
	return (1);
}
