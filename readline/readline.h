/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:54:28 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 20:01:06 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "../libft/libft.h"
# include "../includes/minishell.h"
# include "get_next_line.h"
# include <unistd.h>
# include <signal.h>
# include <term.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include "define.h"
# include "struct.h"

/*
**	readline.c
*/

char			*read_line(char *prompt);

/*
**	init.c
*/

void			init_input(char *prompt);
t_shell			*init_term(t_shell *shell);

/*
**	match_key.c
*/

int				match_key(char *str);

/*
**	print.c
*/

void			print(char *str);
int				take_curs(void);

/*
**	history.c
*/

char			**remake_hist(void);
void			create_history(void);

/*
**	exit.c
*/

char			*return_func(char *str, char *input);
void			mall_check(void);
void			bad_fd_error(int fd, char *tmp);

/*
**	move_left_right.c
*/

void			move_curs_end(void);
void			move_left(void);
void			move_right(void);
void			move_word_left(void);
void			move_word_right(void);

/*
**	delete.c
*/

void			delete_char(void);
void			delete_char_two(void);

/*
**	home_end.c
*/

void			go_home_pos(void);
void			go_end_pos(void);

/*
**	hist_move.c
*/

void			hist_move(int direction);

/*
**	line.c
*/

void			move_end_of_line(void);
void			move_line_down(void);
void			move_line_up(void);

/*
**	free.c
*/

void			free_all(t_shell *shell);
void			ft_free(char *str);
void			null_autocmpl(int time);
void			null_multiline(void);

/*
**	parse_quotes.c
*/

int				parse_quotes(void);

/*
**	signal.c
*/

void			ft_signal_win_size(int signo);

/*
**	autocomplition.c
*/

int				autocmp(char *str);

/*
**	find_file.c
*/

void			find_file(char *key);
void			count_file_match(char *key);
void			find_match(char *key);

/*
**	sort.c
*/

void			ascii_sort(char **array);

/*
**	print_autocompl.c
*/

void			print_array(char **arr);
void			change_input(char **str, char *key);

/*
**	parsepath.c
*/

char			*parse_path(char *tmp);

/*
**	find_cmd.c
*/

void			find_cmd(char *key);

/*
**	find_key.c
*/

char			*find_key(int curs);

/*
**	count_lines.c
*/

void			take_pos(int save_curs);
void			count_lines(void);
void			error_msg(int err, int num, t_shell *shell);
void			scroll_top(void);
void			for_print(char	**str);
char			*check_shift(char *str);
int				putint(int c);
void			del_input(void);
char			*check_curs_pos(int *save_curs, char *buf,\
								char *str, char *tmp);
int				temp_cursor(void);

#endif
