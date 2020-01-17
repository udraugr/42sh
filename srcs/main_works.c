/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_works.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:27:38 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 16:52:07 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_g_semafors(void)
{
	if (g_semafor)
		sem_close(g_semafor);
	if (g_sem_name)
	{
		sem_unlink(g_sem_name);
		free(g_sem_name);
	}
	if (g_bsemafor)
		sem_close(g_bsemafor);
	if (g_bsem_name)
	{
		sem_unlink(g_bsem_name);
		free(g_bsem_name);
	}
	g_semafor = NULL;
	g_bsemafor = NULL;
	g_sem_name = NULL;
	g_sem_name = NULL;
}

void	ft_init_shell_val(char **argv, char **environ)
{
	if (!(g_cmd = malloc(sizeof(t_cmd))))
		exit_shell();
	if (!(g_envi = malloc(sizeof(t_env))))
		exit_shell();
	g_envi->first_list = NULL;
	g_envi->env = ft_dup_char_matr(environ);
	ft_init_glvar(argv);
	g_envi->first_list = ft_create_exe_list();
}

char	*ft_init_loop_read(void)
{
	char	*pr;
	char	*tmp;

	ft_sig_set();
	if (g_check == 1)
		exit(0);
	g_semafor = NULL;
	g_bsemafor = NULL;
	g_sub_str = NULL;
	g_sem_name = NULL;
	g_bsem_name = NULL;
	g_pr_wait = 0;
	g_sem_fl = 0;
	g_bsem_fl = 0;
	ft_print_jobs();
	pr = ft_get_name();
	tmp = rl_gets(pr);
	return (tmp);
}

void	ft_exe_subshell(void)
{
	char	*tmp;
	char	*line_read;

	tmp = NULL;
	if (g_subshell > 0 && g_sub_str && g_shell_num > 0 && !(g_shell_num = 0))
	{
		while (1)
		{
			if (tmp)
				free(tmp);
			tmp = ft_strdup(g_sub_str);
			line_read = ft_strdup(g_sub_str);
			ft_parse_line(line_read);
			free(line_read);
			if (ft_strcmp(tmp, g_sub_str) == 0)
			{
				free(tmp);
				free(g_sub_str);
				break ;
			}
		}
		ft_final_free();
		exit(g_rc);
	}
}
