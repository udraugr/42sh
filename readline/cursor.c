/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 19:58:16 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 20:00:51 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			take_curs(void)
{
	int		curs;
	int		i;
	char	buf[20];

	i = 0;
	ft_bzero(buf, 20);
	ft_putstr_fd("\e[6n", STDIN_FILENO);
	read(STDIN_FILENO, &buf, 20);
	while (buf[i])
	{
		i++;
		if (buf[i - 1] == ';')
			break ;
	}
	curs = ft_atoi(buf + i);
	return (curs);
}

char		*check_curs_pos(int *save_curs, char *buf, char *str, char *tmp)
{
	if (g_input->input_len != g_input->curs_pos - g_input->prompt_len)
	{
		ft_strncpy(buf, g_input->input, g_input->curs_pos\
					- g_input->prompt_len);
		if (str[0] != '\0')
		{
			tmp = ft_strjoin(str, g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos + 1;
		}
		else
		{
			tmp = ft_strdup(g_input->input +\
			g_input->curs_pos - g_input->prompt_len);
			*save_curs = g_input->curs_pos;
		}
		ft_bzero(g_input->input, MAX_CMDS);
		ft_strcpy(g_input->input, buf);
		g_input->input_len = g_input->curs_pos - g_input->prompt_len;
	}
	else
		tmp = ft_strdup(str);
	return (tmp);
}

int			temp_cursor(void)
{
	int		curs;

	curs = 0;
	if (g_input->multiline.pos == 0)
		curs = g_input->curs_pos;
	else
		curs = g_input->curs_pos -\
		g_input->multiline.start[g_input->multiline.pos];
	return (curs);
}
