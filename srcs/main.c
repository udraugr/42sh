/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:27:38 by wveta             #+#    #+#             */
/*   Updated: 2019/12/25 16:51:43 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_set_prcolor(char *ret, char *pr, int j)
{
	if (g_color == 1)
	{
		ret = ft_strcat(ret, CYN);
		if (j > 0)
			ret = ft_strcat(ret, "* ");
		ret = ft_strcat(ret, pr + j);
		ret = ft_strcat(ret, YEL);
		ret = ft_strcat(ret, " > ");
		ret = ft_strcat(ret, RESET);
	}
	else
	{
		if (j > 0)
			ret = ft_strcat(ret, "* ");
		ret = ft_strcat(ret, pr + j);
		ret = ft_strcat(ret, " > ");
	}
	return (ret);
}

char		*ft_get_name(void)
{
	char	*ret;
	char	*pr;
	int		j;

	pr = NULL;
	if (!(pr = ft_get_env2("PWD", g_shell)))
	{
		if (!(pr = ft_strnew(255)))
			exit_shell();
		getcwd(pr, 255);
	}
	j = ft_strlen(pr) - 1;
	(j > 0 && pr[j] == '/') ? j-- : 0;
	while (j >= 0 && pr[j])
	{
		if (pr[j] == '/')
			break ;
		j--;
	}
	if (!(ret = ft_strnew(255)))
		exit_shell();
	ret = ft_set_prcolor(ret, pr, j);
	free(pr);
	return (ret);
}

void		ft_free_list(void)
{
	t_listf	*tmp;

	while (g_envi->first_list)
	{
		if (ft_strequ(g_envi->first_list->file, "") == 1)
		{
			ft_putstr(g_envi->first_list->path);
			ft_putstr("\n");
		}
		if (g_envi->first_list->file)
			free(g_envi->first_list->file);
		if (g_envi->first_list->path)
			free(g_envi->first_list->path);
		tmp = g_envi->first_list;
		g_envi->first_list = g_envi->first_list->next;
		free(tmp);
	}
}

void		ft_final_free(void)
{
	if (g_envi->hash_first)
		ft_hash_all_del(NULL);
	g_envi->env = ft_free_char_matr(g_envi->env);
	ft_free_list();
	free(g_envi);
	g_cmd->cmd_list = ft_free_char_matr(g_cmd->cmd_list);
	free(g_cmd);
	g_shell = ft_free_char_matr(g_shell);
	free(g_app_full_name);
	if (g_subshell > 0)
		return ;
}

int			main(int argc, char **argv, char **environ)
{
	char	*line_read;

	ft_init_shell_val(argv, environ);
	g_cmd->jmp_code = setjmp(g_cmd->ebuf);
	while (g_subshell == 0 && argc == 1)
	{
		line_read = ft_init_loop_read();
		ft_parse_line(line_read);
		free(line_read);
		ft_exe_subshell();
	}
	ft_final_free();
	return (0);
}
