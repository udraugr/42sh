/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:43:17 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:48:49 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/arithmetic.h"
#include <stdio.h>

static void			ft_print_error_message_arithmetic(char *str)
{
	char			*event;

	event = ft_strjoin(" : ", str);
	event = ft_strfjoin(event, " : ");
	ft_print_msg(event, g_error_arithmetic);
	ft_strdel(&event);
	ft_strdel(&g_error_arithmetic);
}

static void			error_output_calc(char *str)
{
	if (!g_error_arithmetic && g_lexem)
		syntax_error_found();
	ft_print_error_message_arithmetic(str);
}

char				*calculator(char *str)
{
	t_list			*lexem;
	int32_t			result;
	char			*ans;

	result = 0;
	g_error_arithmetic = 0;
	g_lexem = 0;
	g_correct_values = 0;
	lexem = parser_str(str);
	ans = 0;
	if (g_error_arithmetic)
		ft_print_error_message_arithmetic(str);
	else
	{
		g_lexem = lexem;
		result = expr();
		if (!g_error_arithmetic && !g_lexem)
			ans = ft_itoa(result);
		else
			error_output_calc(str);
	}
	lst_del(&lexem, destroy_lexem);
	return (ans);
}
