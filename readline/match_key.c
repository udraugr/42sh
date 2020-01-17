/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:06:58 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 14:55:45 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	color_sign_key(char *str)
{
	if (str[0] == SET_COLOR && str[1] == '\0')
	{
		g_color = g_color * (-1);
		ft_putstr_fd("\n", 2);
		if (g_color == 1)
			ft_print_msg(": set colors:", " ON");
		else
			ft_print_msg(": set colors:", " OFF");
	}
	else if (str[0] == SET_SIG && str[1] == '\0')
	{
		g_signal = g_signal * (-1);
		ft_putstr_fd("\n", 2);
		if (g_signal == 1)
			ft_print_msg(": set signals:", " ON");
		else
			ft_print_msg(": set signals:", " OFF");
	}
	return (0);
}

static int	match_del_hist_key(char *str)
{
	if (str[0] == BACKSPACE && !str[1])
		delete_char();
	else if (!(ft_strcmp(str, DEL)))
		delete_char_two();
	else if ((!(ft_strcmp(str, UP_ARR))) || (!(ft_strcmp(str, "\eOA"))))
		hist_move(0);
	else if ((!(ft_strcmp(str, DOWN_ARR))) || (!(ft_strcmp(str, "\eOB"))))
		hist_move(1);
	else if (str[0] == CTRL_L && !str[1])
		scroll_top();
	else if (str[0] == CTRL_K && !str[1])
		del_input();
	else
		return (0);
	return (1);
}

static int	match_move_key(char *str)
{
	if ((!(ft_strcmp(str, LEFT_ARR))) || (!(ft_strcmp(str, "\eOD"))))
		move_left();
	else if ((!(ft_strcmp(str, RIGHT_ARR))) || (!(ft_strcmp(str, "\eOC"))))
		move_right();
	else if (!(ft_strcmp(str, CTRL_LEFT)))
		move_word_left();
	else if (!(ft_strcmp(str, CTRL_RIGHT)))
		move_word_right();
	else if (!(ft_strcmp(str, HOME)))
		go_home_pos();
	else if (!(ft_strcmp(str, END)))
		go_end_pos();
	else if (!(ft_strcmp(str, CTRL_UP)))
		move_line_up();
	else if (!(ft_strcmp(str, CTRL_DOWN)))
		move_line_down();
	else
		return (0);
	return (1);
}

int			match_key(char *str)
{
	color_sign_key(str);
	if (match_move_key(str) || match_del_hist_key(str))
		return (1);
	return (0);
}
