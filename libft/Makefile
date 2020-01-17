# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thaley <thaley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 12:47:16 by wveta             #+#    #+#              #
#    Updated: 2019/12/08 02:16:41 by thaley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS := -g -Wall -Werror -Wextra 
INCLUDES := -I$(HEADER_DIR)
HEADER_DIR := .

SRC := ft_bzero.c  ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c\
    ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
    ft_strstr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c\
	ft_isalnum.c ft_isprint.c ft_isascii.c ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c ft_strnew.c\
	ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c\
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c\
	ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c\
	ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c\
	ft_isspace.c ft_isupper.c ft_isblank.c ft_islower.c ft_isxdigit.c\
	ft_strfjoin.c ft_free_table.c ft_lst_sort.c ft_lstadd_last.c ft_lstsize.c ft_strndup.c\
	ft_isnumber.c ft_strchrlen.c ft_strnjoin.c

OBJECT_LIST := $(SRC:.c=.o)

all: $(NAME)

.PHONY: all clean fclean

$(NAME): $(OBJECT_LIST)
	@/usr/bin/ar rcs $(NAME) $(OBJECT_LIST)
	@/usr/bin/ranlib $(NAME)
	@printf "\r\033[32;1mCreate $(NAME)!                                     \n\033[0m"
	@printf "\033[?25h"

%.o: %.c $(HEADER_DIR)/libft.h
	@printf "\033[?25l"
	@/usr/bin/clang $(INCLUDE) $(CFLAGS) -o $@ -c $<
	@printf "\r\033[34;1mNow compiling $@!                                   \033[0m"

clean:
	@/bin/rm -f $(OBJECT_LIST)
	@printf "\r\033[31mDell all .o files!                                     \n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\r\033[31;1mDell $(NAME)!                                        \n\033[0m"

re:	fclean all
