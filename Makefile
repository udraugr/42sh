NAME	:=	42sh
FILES	:=	built_in exec_list ft_built_cd ft_built_env main parser\
			readline_sh sort utils utils2 utils3 utils4 utils5\
			do_cmd_shellrev ft_split_pipes ft_calc_full_path\
			ft_redir_2less ft_redir_great ft_redir_less \
			ft_test_pipes ft_test_redir redir_io_rest utils_dup\
			utils_great utils_great2 utils_pipe utils_pipe2 utils_pipe3\
			utils_pipe_split utils_pipe_split2 utils_great3\
			ft_get_less_tst hash heredoc ft_replace exec_list2\
			ft_built_cd2 locals ft_built_env2 ft_built_env3 \
			ft_built_env4 ft_replays_subs hash_cmd hash_cmd_add\
			ft_par_exp ft_par_exp2 ft_jobs ft_signals ft_jobs_struct\
			ft_job_print ft_job_print_next ft_job_proc ft_print_job_line\
			buil_in_jobs ft_signals_next buil_in_jobs_bg built_in_kill\
			globbing glob_check ft_signals_child ft_alias ft_unalias\
			fts_for_alias ft_read_alias ft_get_alias fts_output_alias\
			semafor param_remove ft_cntrl_subst ft_calc check_str\
			bin_test_binary bin_test_misc bin_test_unary bin_test\
			glob_join buil_in_jobs_bg_cmd built_in_kill_cmd do_cmd_shell_norm\
			ft_calc_str_test ft_calc_str_test2 ft_cntrl_subst2 ft_jobs_test\
			ft_par_exp1 ft_par_exp3 ft_repl_check ft_split_words ft_type\
			ft_exit ft_split_words_cut globbing_dup hash_cmd_dup main_works\
			param_remove_dup parser_dup utils_pipe4 utils_pipe5 utils_pipe6\
			del_ekran ft_redir_less2 ft_split_words_cut2 ft_split_words_cut3\
			ft_do_export ft_get_heof ft_get_fd_by_n

SRC_D	:=	srcs
INC_D	:=	includes
OBJ_D	:=	objs
LIB_D	:=	libft
LIB_D2	:=	readline

include	$(SRC_D)/calc/calc_files.mk

SRC		:=	$(addprefix $(SRC_D)/, $(patsubst %, %.c, $(FILES)) $(SRC_CALC))
OBJ		:=	$(addprefix $(OBJ_D)/, $(patsubst %, %.o, $(FILES)) $(OBJ_CALC)) 

SUB_DIR := $(OBJ_D) $(SUB_DIR_CALC)

FLAGS	:=	-g -Wall -Wextra -Werror
LIB_LNK :=	-L$(LIB_D) -lft $(LIB_D2)/readline.a -ltermcap

.PHONY: clean fclean re begin_work

all: begin_work $(NAME)

begin_work:
	@make -C $(LIB_D)
	@make -C $(LIB_D2)

$(SUB_DIR):
	@mkdir $@

$(NAME): libft/libft.a readline/readline.a $(SUB_DIR) $(OBJ)
	@gcc $(FLAGS) $(OBJ) $(LIB_LNK) -lreadline -o $(NAME)
	@printf "\r\033[32;1mCreate $(NAME)!                                      \n\033[0m"
	@printf "\033[?25h"

$(OBJ_D)/%.o: $(SRC_D)/%.c $(INC_D)/minishell.h $(HEADER_CALC)
	@printf "\033[?25l"
	@gcc -I$(INC_D) -I$(LIB_D) -I$(INCL_DIR_CALC) $(FLAGS) -o $@ -c $<
	@printf "\r\033[34;1mNow compiling $@!                                    \033[0m"

clean:
	@make -C $(LIB_D) fclean
	@make -C $(LIB_D2) fclean
	@/bin/rm -f $(OBJ)
	@printf "\r\033[31mDell all for $(NAME)!                                  \n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "\r\033[31;1mDell $(NAME)!                                        \n\033[0m"

re: fclean all
