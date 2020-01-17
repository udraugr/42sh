/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/12/23 12:47:01 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_putfnbr(int nb, char *str)
{
	int		a;
	int		b;
	int		len;
	char	c;

	if (nb == -2147483648)
		str = ft_strcat(str, "-");
	else
	{
		if (nb < 0)
		{
			nb = nb * (-1);
			str = ft_strcat(str, "-");
		}
		a = nb / 10;
		b = nb % 10;
		if (a > 0)
			str = ft_putfnbr(a, str);
		len = ft_strlen(str);
		c = b + 48;
		str[len] = c;
		str[len + 1] = '\0';
	}
	return (str);
}

int		ft_print_hash(void)
{
	t_listh	*tmp;
	int		count;
	char	*str;
	int		len;

	count = 0;
	tmp = g_envi->hash_first;
	str = ft_alloc_char(500);
	while (tmp)
	{
		str[0] = '\0';
		if ((count = count + 1) && count == 1)
			ft_putstr("hits	command\n");
		str = ft_putfnbr(tmp->hashcount, str);
		len = ft_strlen(str);
		if (len < 4)
			str = ft_strncat(str, "    ", 4 - len);
		str = ft_strcat(str, "   ");
		str = ft_strcat(str, tmp->path);
		str = ft_strcat(str, "\n");
		write(STDOUT_FILENO, str, ft_strlen(str));
		tmp = tmp->next;
	}
	free(str);
	return (1);
}

void	cmd_hash_body_end(char **av, int i, int *start, int *fl)
{
	if (*start == 0)
		*start = i;
	if (*fl == 4)
		ft_hash_all_del(av[i]);
	else if (*fl == 3)
	{
		if (i > *start)
			ft_hash_cmd_add(av[*start], av[i], 0);
	}
	else if (*fl == 2 && ((i - *start > 0) || (av[i + 1])))
		ft_print_one(av[i], 2);
	else if (*fl == 2)
		ft_print_one(av[i], 1);
	else if (*fl == 1)
		ft_print_one(av[i], 3);
}

void	cmd_hash_body(char **av, int i, int *start, int *fl)
{
	if (av[i][0] == '-' && ft_strchr(av[i], 'r'))
		ft_hash_all_del(NULL);
	else if (av[i][0] == '-' && ft_strchr(av[i], 'd'))
		*fl = 4;
	else if (av[i][0] == '-' && ft_strchr(av[i], 'p') && *fl < 4)
		*fl = 3;
	else if (av[i][0] == '-' && ft_strchr(av[i], 't') && *fl < 3)
		*fl = 2;
	else if (av[i][0] == '-' && ft_strchr(av[i], 'l') && *fl < 2
		&& (av[i + 1]))
		*fl = 1;
	else if (av[i][0] == '-' && ft_strchr(av[i], 'l') && *fl < 2
			&& !(av[i + 1]))
		ft_print_one(NULL, 3);
	else if (av[i][0] == '-')
		ft_hash_usage(av[i]);
	else
		cmd_hash_body_end(av, i, start, fl);
}

int		ft_cmd_hash(char **av)
{
	int		i;
	char	*tmp;
	int		fl;
	int		start;

	ft_set_shell("?", "0");
	i = 1;
	fl = 0;
	tmp = NULL;
	start = 0;
	if (!(av[1]))
		return (ft_print_hash());
	while (av && av[i])
	{
		cmd_hash_body(av, i, &start, &fl);
		i++;
	}
	return (1);
}
