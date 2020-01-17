/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:46:12 by thaley            #+#    #+#             */
/*   Updated: 2019/12/11 20:21:25 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			parse_backslash(int start)
{
	int		count;

	count = 0;
	if (start < 0)
		return (-1);
	if (g_input->input[start] == '\\' && start > -1)
	{
		while (start > -1 && start != g_input->input_len
			&& g_input->input[start] == '\\')
		{
			start--;
			count++;
		}
	}
	return (count);
}

int			dop_check(int i, int b_sl)
{
	if (g_input->start_quotes != i && g_input->quotes == '\0'\
		&& g_input->input[i] == '"' && (i == 0 || b_sl == 0))
	{
		g_input->quotes = '"';
		g_input->start_quotes = i;
	}
	else if (g_input->start_quotes != i && ((g_input->quotes == '"'\
			&& g_input->input[i] == '"') || (g_input->quotes == '\''\
			&& g_input->input[i] == '\'')) && (i == 0 || b_sl == 0))
	{
		g_input->quotes = '\0';
		g_input->start_quotes = -1;
	}
	else if (g_input->start_quotes != i && g_input->quotes == '\0'\
		&& g_input->input[i] == '\'' && (i == 0 || b_sl == 0))
	{
		g_input->quotes = '\'';
		g_input->start_quotes = i;
	}
	return (i);
}

int			check_quotes(void)
{
	int		i;
	int		b_sl;

	i = 0;
	if (g_input->start_quotes != -1)
		i = g_input->start_quotes;
	b_sl = 0;
	while (i < g_input->input_len)
	{
		if (g_input->quotes != '\'' && g_input->input[i] == '\\')
		{
			b_sl++;
			b_sl = b_sl % 2;
		}
		i = dop_check(i, b_sl);
		if (b_sl == 1 && g_input->input[i] != '\\')
			b_sl = 0;
		i++;
	}
	if (g_input->quotes == '\0')
	{
		g_input->start_quotes = -1;
		return (0);
	}
	return (1);
}

int			parse_quotes(void)
{
	int				i;

	i = parse_backslash(g_input->input_len - 1);
	if (i % 2 != 0 && i > -1)
		return (1);
	if (check_quotes())
		return (1);
	return (0);
}
