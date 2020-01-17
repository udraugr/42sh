# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thaley <thaley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 13:59:52 by thaley            #+#    #+#              #
#    Updated: 2019/12/26 20:03:56 by thaley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= readline.a
FILES		:= readline init match_key get_next_line\
	print exit move_left_right history delete home_end\
	hist_move line free parse_quotes signal autocomplition\
	find_file ascii_sort print_autocmpl parsepath find_cmd\
	find_key count_lines init_term shift error cursor

SRC			:= $(patsubst %, %.c, $(FILES))
OBJ			:= $(patsubst %, %.o, $(FILES))

INCL_DIR	:= ../libft

FLAGS		:= -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "\r\033[32;1mCreate $(NAME)!                                      \n\033[0m"
	@printf "\033[?25h"

get_next_line.o: get_next_line.c $(INCL_DIR)/libft.h get_next_line.h readline.h struct.h define.h
	@printf "\033[?25l"
	@gcc $(FLAGS) -I$(INCL_DIR) -o $@ -c $<
	@printf "\r\033[34;1mNow compiling $@!                                    \033[0m"

%.o: %.c $(INCL_DIR)/libft.h readline.h struct.h define.h
	@printf "\033[?25l"
	@gcc $(FLAGS) -I$(INCL_DIR) -o $@ -c $<
	@printf "\r\033[34;1mNow compiling $@!                                    \033[0m"

so:
	@gcc -shared -o readline.so -fPIC *.c -I ../libft

clean:
	@/bin/rm -f $(OBJ)
	@printf "\r\033[31mDell all o files!                                      \n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\r\033[31;1mDell $(NAME)!                                        \n\033[0m"

re: fclean all
