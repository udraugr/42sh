/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:58:21 by thaley            #+#    #+#             */
/*   Updated: 2019/12/18 05:07:57 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "readline.h"

typedef struct		s_hist
{
	char			**cmd;
	char			*path;
	int				amount;
	int				pos;
}					t_hist;
t_hist				*g_hist;

typedef struct		s_tab
{
	char			**seach_res;
	char			*path;
	int				save_curs;
	int				amount;
	int				file;
	int				cmd;
	int				key_check;
	int				tab_count;
	int				max_len;
	int				num_in_row;
	int				col_pos;
}					t_tab;

typedef struct		s_shell
{
	char			*term;
	struct termios	new_param;
	struct termios	old_param;
}					t_shell;

typedef struct		s_multi
{
	int				num_of_lines;
	int				pos;
	int				start[MAX_CMDS];
	int				end[MAX_CMDS];
}					t_multi;

typedef struct		s_input
{
	struct winsize	ws;
	t_tab			autocompl;
	t_multi			multiline;
	char			input[MAX_CMDS];
	char			old_input[MAX_CMDS];
	char			copy[MAX_CMDS];
	char			*prompt;
	char			quotes;
	int				start_quotes;
	int				old_in_check;
	int				input_len;
	int				prompt_len;
	int				curs_pos;
	int				heredoc;
}					t_input;
t_input				*g_input;

#endif
