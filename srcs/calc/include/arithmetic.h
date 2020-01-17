/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:42:44 by udraugr-          #+#    #+#             */
/*   Updated: 2019/12/10 18:26:49 by udraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

# include "../../../includes/minishell.h"

enum {SUCCESS = 0, FAIL = -1};
enum {VAR = 1000, NUMB = 1001, OPER = 1002};
enum {INCREMENT = 0, DECREMENT = 1,
	PLUS = 2, MINUS = 3, MULTIPLICATION = 4, DIVISION = 5, MODULE = 6,
	LE = 7, GE = 8, LESSER = 9, GREATER = 10, EQUAL = 11, NOT_EQUAL = 12,
	AND = 13, OR = 14,
	LBRACE = 15, RBRACE = 16};

char				*g_error_arithmetic;
t_list				*g_lexem;
int32_t				g_correct_values;

typedef struct		s_oper
{
	uint32_t		id;
}					t_oper;

typedef struct		s_var
{
	char			*name;
	int32_t			value;
}					t_var;

typedef struct		s_numb
{
	int32_t			numb;
}					t_numb;

t_list				*lst_create(void *content, size_t type);
void				lst_del(t_list **lst, void (*f)(void *, size_t));

t_numb				*create_numb(int32_t numb);
t_oper				*create_oper(int32_t id);
t_var				*create_var(char *name, int32_t value);
void				destroy_lexem(void *lexem, size_t type);

t_list				*parser_str(char *str);

int32_t				is_it_spaces(char c);
int32_t				is_it_operator(char *str);
int32_t				is_it_var(char *str, uint32_t len_numb);

int32_t				it_operator(char *str, t_list **lexem);
void				check_increment_decrement(char *str, t_list **lexem,
										uint32_t *id, uint32_t *len_oper);
int32_t				ft_atoi_base(char *str, int32_t base, uint32_t *len_numb);
int32_t				it_variable(char *str, t_list **lexem);
int32_t				it_number(char *str, t_list **lexem);

int32_t				expr(void);
int32_t				expr_or(void);
int32_t				expr_and(void);
int32_t				expr_equal(void);
int32_t				expr_relat_op(void);
int32_t				expr_additive(void);
int32_t				expr_multiplicativ(void);
int32_t				expr_unar(void);
int32_t				expr_prefix(void);
int32_t				expr_suffix(void);
int32_t				expr_barckets(void);
int32_t				expr_return_value(void);

int32_t				take_var_value(char *name);
void				change_var_value(char *name, int32_t operation);

void				syntax_error_found(void);

char				*calculator(char *str);

#endif
