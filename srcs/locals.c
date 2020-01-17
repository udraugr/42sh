/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/12/12 15:09:19 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_init_shell(void)
{
	int i;

	i = ft_calc_matr_rows(g_envi->env);
	if (!(g_shell = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	g_shell[i + 1] = NULL;
	i = -1;
	while (g_envi->env[++i])
		g_shell[i] = ft_strdup(g_envi->env[i]);
	if (!(g_shell[i] = ft_strdup("?=0")))
	{
		ft_free_char_matr(g_shell);
		g_shell = NULL;
		return (g_shell);
	}
	return (g_shell);
}

static void	ft_init_glvar_begin(void)
{
	g_check = 0;
	g_color = 1;
	g_signal = -1;
	g_subs_counter = 0;
	g_shell = NULL;
	g_shell = ft_init_shell();
	g_and_or = 0;
	g_and_or_line = 0;
	g_not = 0;
	g_rc = 0;
	g_built_rc = 0;
	g_job_first = NULL;
	g_job_last = NULL;
	g_job_ind = 1;
	g_job = -1;
	g_subst = 0;
	g_envi->hash_first = NULL;
	g_subshell = 0;
	g_parent_pid = getpid();
	g_shell_num = 0;
}

void		ft_init_glvar(char **av)
{
	ft_init_glvar_begin();
	g_app_name = ft_get_app_name(av[0]);
	if ((av[0][0] == '.') || (ft_check_file(av[0], X_OK) == -1))
	{
		g_app_full_name = ft_get_env("PWD");
		g_app_full_name = ft_strfjoin(g_app_full_name, "/");
		g_app_full_name = ft_strfjoin(g_app_full_name, g_app_name);
	}
	else
		g_app_full_name = ft_strdup(av[0]);
	g_std_in = dup(STDIN_FILENO);
	g_std_out = dup(STDOUT_FILENO);
	g_stderr = dup(STDERR_FILENO);
	g_terminal = STDIN_FILENO;
	g_is_interactive = isatty(g_terminal);
	tcgetattr(g_terminal, &g_tmodes);
}

char		**ft_isnot(char **in)
{
	char	**av;

	av = in;
	if (ft_strcmp(av[0], "!") == 0)
	{
		g_not = 1;
		av[0][0] = '\0';
		av = ft_press_matr(av);
	}
	return (av);
}
