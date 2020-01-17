/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:24:23 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 17:53:55 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/arithmetic.h"

int32_t					is_it_spaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (SUCCESS);
	return (FAIL);
}

static void				*ft_terminate(t_list **lexem)
{
	lst_del(lexem, &destroy_lexem);
	return (0);
}

static char				*error_mes(char *str)
{
	char				*ans;
	char				*tmp;

	tmp = ft_strjoin("(error token is \"", str);
	ans = ft_strjoin("syntax error: invalid arithmetic operator ", tmp);
	ft_strdel(&tmp);
	tmp = ans;
	ans = ft_strjoin(ans, "\")");
	ft_strdel(&tmp);
	return (ans);
}

t_list					*parser_str(char *str)
{
	uint32_t			i;
	uint32_t			result;
	t_list				*lexem;

	lexem = 0;
	i = 0;
	while (str[i])
	{
		result = 0;
		if (is_it_spaces(str[i]) == SUCCESS)
			++i;
		else if (is_it_operator(&str[i]) == SUCCESS)
			result = it_operator(&str[i], &lexem);
		else if (ft_isdigit(str[i]) == 1)
			result = it_number(&str[i], &lexem);
		else if (is_it_var(&str[i], 0) == SUCCESS)
			result = it_variable(&str[i], &lexem);
		else
		{
			g_error_arithmetic = error_mes(&str[i]);
			return (ft_terminate(&lexem));
		}
		i += result;
	}
	return (lexem);
}
