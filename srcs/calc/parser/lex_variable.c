/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:33:21 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:52:08 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

static int				ft_is_var_name(char c, int first_char)
{
	if (
		(c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '_'
		|| (!first_char && ft_isdigit(c)))
		return (SUCCESS);
	return (FAIL);
}

int32_t					is_it_var(char *str, uint32_t len_numb)
{
	while (*str && !len_numb && is_it_spaces(*str) == SUCCESS)
		++str;
	if (*str && ft_is_var_name(*str, !len_numb) == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int32_t					it_variable(char *str, t_list **lexem)
{
	uint32_t			len_var;
	uint32_t			i;
	char				*var_name;
	t_var				*new_var;
	t_list				*new;

	len_var = 0;
	i = 0;
	while (str[i] && is_it_var(&str[i], len_var) == SUCCESS)
	{
		++i;
		++len_var;
	}
	var_name = ft_strndup(str, len_var);
	new_var = create_var(var_name, 0);
	ft_strdel(&var_name);
	new = lst_create((void *)new_var, VAR);
	ft_lstadd_last(lexem, new);
	return (len_var);
}
