/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_kill_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/12/02 15:27:57 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_kill_job_by_num(int i, int sig, pid_t num, char **av)
{
	t_job	*j;
	t_proc	*p;

	num = ft_atoi(av[i] + 1);
	j = g_job_first;
	while (j)
	{
		if (j->num == num || (num == 0 && j->flag == '+'))
		{
			p = j->first_proc;
			while (p)
			{
				num = p->pid;
				kill(num, sig);
				p = p->next;
			}
			break ;
		}
		j = j->next;
	}
	if (num == ft_atoi(av[i] + 1))
	{
		ft_print_msg(": kill : no such job: ", av[i] + 1);
		ft_set_shell("?", "1");
	}
}

void	ft_kill_set_proc(char **av, int i, int sig)
{
	pid_t	num;

	while (av[++i])
	{
		num = 0;
		if (av[i][0] == '%')
			ft_kill_job_by_num(i, sig, num, av);
		else
		{
			num = ft_atoi(av[i]);
			if ((kill(num, 0)) != 0)
			{
				ft_print_msg(" kill : no such process: ", av[i]);
				continue ;
			}
			kill(num, sig);
		}
	}
}

int		ft_kill_set_sig(int *sig, int *i, char **av, char **signame)
{
	*sig = 0;
	if (av[1] && av[1][0] == '-')
	{
		*i = -1;
		if (*(av[1] + 1) >= '0' && *(av[1] + 1) <= '9' && ((*i = 1)))
			*sig = ft_atoi(av[1] + 1);
		else
		{
			while (signame[++*i] && *sig == 0)
			{
				if (ft_strcmp(av[1] + 1, signame[*i]) == 0 && ((*sig = *i + 1)))
					*i = 0;
			}
		}
		if (*sig == 0)
		{
			ft_print_msg(": kill : invalid signal specification: ", av[1] + 1);
			ft_set_shell("?", "1");
			return (1);
		}
	}
	else if (((*i = 0)) == 0)
		*sig = 9;
	return (0);
}

int		ft_cmd_kill(char **av)
{
	int		sig;
	char	**signame;
	int		i;

	ft_set_shell("?", "0");
	signame = ft_split_pipes("HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV \
	SYS PIPE ALRM TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM \
	PROF WINCH INFO USR1 USR2");
	if (ft_kill_set_sig(&sig, &i, av, signame) == 1)
		return (1);
	ft_free_char_matr(signame);
	ft_kill_set_proc(av, i, sig);
	return (1);
}
