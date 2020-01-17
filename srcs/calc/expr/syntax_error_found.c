/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_found.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 10:16:34 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:06:37 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static char				*take_oper(int32_t id)
{
	char				**opers;

	opers = (char*[]){"++", "--", "+", "-", "*", "/", "%",
							"<=", ">=", "<", ">",
							"==", "!=",
							"&&", "||",
							"(", ")",
							0};
	return (ft_strdup(opers[id]));
}

static char				*take_token(void)
{
	if (!g_lexem)
		return (ft_strdup(" "));
	else if (g_lexem->content_size == NUMB)
		return (ft_itoa(((t_numb *)g_lexem->content)->numb));
	else if (g_lexem->content_size == VAR)
		return (ft_strdup(((t_var *)g_lexem->content)->name));
	else
		return (take_oper(((t_oper *)g_lexem->content)->id));
}

void					syntax_error_found(void)
{
	char				*mes;
	char				*oper;

	mes = ft_strdup("syntax error: operand expected (error token is \"");
	oper = ft_strfjoin(take_token(), "\")");
	g_error_arithmetic = ft_strjoin(mes, oper);
	ft_strdel(&mes);
	ft_strdel(&oper);
}
