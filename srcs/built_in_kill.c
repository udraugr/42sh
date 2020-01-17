/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_kill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/12/02 15:31:50 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_cmd_exit_status(int status)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * 3);
	if (tmp)
	{
		tmp[0] = '\0';
		if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) != 0)
			ft_set_shell("?", "1");
		else if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) == 0)
			ft_set_shell("?", "0");
		else if (WIFSTOPPED(status))
			ft_set_shell("?", ft_putfnbr(WSTOPSIG(status), tmp));
		else if (WIFSIGNALED(status))
			ft_set_shell("?", ft_putfnbr(WTERMSIG(status), tmp));
		else if (WIFCONTINUED(status))
			ft_set_shell("?", "0");
		else
			ft_set_shell("?", "1");
		free(tmp);
	}
}

void	ft_rec_log(char *str)
{
	int i;

	i = open("/tmp/42shlog", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (i != -1)
	{
		write(i, "\n", 1);
		write(i, str, ft_strlen(str));
	}
	close(i);
}

int		ft_get_cmd_exit_status(int status)
{
	int	rc;
	int	i;

	rc = 0;
	if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) != 0)
		rc = 1;
	else if ((WIFEXITED(status)) && (i = WEXITSTATUS(status)) == 0)
		rc = 0;
	else if (WIFSTOPPED(status))
		rc = WSTOPSIG(status);
	else if (WIFSIGNALED(status))
		rc = WTERMSIG(status);
	else if (WIFCONTINUED(status))
		rc = 0;
	else
		rc = 1;
	return (rc);
}

char	*ft_get_app_name(char *s)
{
	int		j;

	j = ft_strlen(s) - 1;
	while (j >= 0 && s[j])
	{
		if (s[j] == '/')
			break ;
		j--;
	}
	return (s + j + 1);
}
