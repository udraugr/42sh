/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 20:08:52 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:55:54 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t				is_it_operator(char *str)
{
	char				**operators;
	uint32_t			i;

	operators = (char*[]){"++", "--", "+", "-", "*", "/", "%",
							"<=", ">=", "<", ">",
							"==", "!=",
							"&&", "||",
							"(", ")",
							0};
	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(str, operators[i], ft_strlen(operators[i])) == 0)
			return (SUCCESS);
		++i;
	}
	return (FAIL);
}

int32_t				it_operator(char *str, t_list **lexem)
{
	char				**operators;
	uint32_t			id;
	uint32_t			len_oper;
	t_oper				*new_oper;
	t_list				*new;

	operators = (char *[]){"++", "--", "+", "-", "*", "/", "%",
							"<=", ">=", "<", ">",
							"==", "!=", "&&", "||", "(", ")", 0};
	id = 0;
	while (operators[id])
	{
		len_oper = ft_strlen(operators[id]);
		if (strncmp(str, operators[id], len_oper) == 0)
		{
			if (id == INCREMENT || id == DECREMENT)
				check_increment_decrement(str, lexem, &id, &len_oper);
			new_oper = create_oper(id);
			new = lst_create((void *)new_oper, OPER);
			ft_lstadd_last(lexem, new);
			return (len_oper);
		}
		++id;
	}
	return (0);
}
