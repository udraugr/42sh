# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calc_files.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: udraugr- <udraugr-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 11:07:09 by udraugr-          #+#    #+#              #
#    Updated: 2019/11/21 15:35:30 by udraugr-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GENERAL_DIR_CALC	:=	calc

PARS_DIR:=	parser
SRC_PARS:=	\
			lex_numb.c\
			lex_operator.c\
			lex_variable.c\
			lexem_create.c\
			lexem_destroy.c\
			parser.c\
			check_increment_decrement.c\
			fts_lst.c
SRC_PARS:= $(addprefix $(PARS_DIR)/, $(SRC_PARS))

EXPR_DIR:=	expr
SRC_EXPR:=	\
			expr.c\
			expr_additive.c\
			expr_and.c\
			expr_barckets.c\
			expr_equal.c\
			expr_multiplicativ.c\
			expr_or.c\
			expr_prefix.c\
			expr_relat_op.c\
			expr_return_value.c\
			expr_suffix.c\
			expr_unar.c\
			syntax_error_found.c\
			var_functions.c
			
SRC_EXPR:= $(addprefix $(EXPR_DIR)/, $(SRC_EXPR))

SRC_CALC:=	$(SRC_PARS) $(SRC_EXPR) calc.c
SRC_CALC:= 	$(addprefix $(GENERAL_DIR_CALC)/, $(SRC_CALC))

OBJ_CALC:=	$(SRC_CALC:.c=.o)

OBJ_DIR_CALC		:= objs
SUB_DIR_CALC		:=	\
						$(OBJ_DIR_CALC)/$(GENERAL_DIR_CALC)\
						$(OBJ_DIR_CALC)/$(GENERAL_DIR_CALC)/$(PARS_DIR)\
						$(OBJ_DIR_CALC)/$(GENERAL_DIR_CALC)/$(EXPR_DIR)

INCL_DIR_CALC		:=	srcs/calc/include
HEADER_CALC			:=	srcs/calc/include/arithmetic.h
