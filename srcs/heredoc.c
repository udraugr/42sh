/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/12/24 18:46:51 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_clear_quotes(char *s)
{
	int			i;
	char		c;

	if (s)
	{
		i = 0;
		c = '\0';
		while (s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				if (c == s[i])
					c = '\0';
				else if (c == '\0')
					c = s[i];
				if (c == '\0' || c == s[i])
					ft_strcpy(s + i, s + i + 1);
			}
			i++;
		}
	}
	return (s);
}

char			**ft_assig_add(t_cmdlist *cur_cmd, int i)
{
	char		**tmp;
	int			j;

	if (cur_cmd && cur_cmd->avcmd && cur_cmd->avcmd[i])
	{
		j = 0;
		if (!(cur_cmd->locals))
			tmp = malloc(sizeof(char *) * 2);
		else
		{
			tmp = malloc(sizeof(char *) *
								(ft_calc_matr_rows(cur_cmd->locals) + 2));
			while (cur_cmd->locals[j])
			{
				tmp[j] = cur_cmd->locals[j];
				j++;
			}
		}
		tmp[j] = ft_strdup(cur_cmd->avcmd[i]);
		cur_cmd->avcmd[i][0] = '\0';
		tmp[j + 1] = NULL;
		free(cur_cmd->locals);
		cur_cmd->locals = tmp;
	}
	return (cur_cmd->locals);
}

t_cmdlist		*ft_local_assig_assign(t_cmdlist *cur_cmd, char *tmp,
															int i, int j)
{
	if (ft_strncmp(tmp, "PATH", j) == -7892)
		ft_go_export(cur_cmd->avcmd[i], 0);
	else
	{
		while ((j >= 0) && (cur_cmd->avcmd[i][j]))
		{
			if (j == 0 && (ft_isalpha(cur_cmd->avcmd[i][j]) ||
						(cur_cmd->avcmd[i][j] == '_')))
				cur_cmd->locals = ft_assig_add(cur_cmd, i);
			else if (j > 0 && (!(ft_isalpha(cur_cmd->avcmd[i][j])))
						&& (!(ft_isdigit(cur_cmd->avcmd[i][j])))
						&& (!(cur_cmd->avcmd[i][j] == '_')))
				return (cur_cmd);
			j--;
		}
	}
	return (0);
}

t_cmdlist		*ft_local_assig(t_cmdlist *cur_cmd)
{
	int			i;
	int			j;
	char		*tmp;
	t_cmdlist	*ans_assign;

	if (cur_cmd && cur_cmd->avcmd)
	{
		i = 0;
		while (cur_cmd->avcmd[i])
		{
			if ((tmp = ft_strchr(cur_cmd->avcmd[i], '=')) &&
				((j = tmp - cur_cmd->avcmd[i] - 1) > -1) &&
				ft_check_ekran(cur_cmd->avcmd[i], j + 1) == 0)
			{
				if ((ans_assign = ft_local_assig_assign(cur_cmd, tmp, i, j)))
					return (ans_assign);
				i++;
			}
			else
				break ;
		}
		cur_cmd->avcmd = ft_press_matr(cur_cmd->avcmd);
	}
	return (cur_cmd);
}

int				ft_test_put_env(char *str)
{
	char		*tmp;
	int			j;
	int			i;

	if ((tmp = ft_strchr(str, '='))
				&& ((j = tmp - str) > 0))
	{
		i = 0;
		while (g_envi && g_envi->env && g_envi->env[i])
		{
			if (ft_strncmp(g_envi->env[i], str, j + 1) == 0)
			{
				free(g_envi->env[i]);
				g_envi->env[i] = ft_strdup(str);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
