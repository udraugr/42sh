/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:00:14 by thaley            #+#    #+#             */
/*   Updated: 2019/12/26 14:54:55 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BSIZE		1
# define MAX_CMDS	4096
# define ENTER		10

/*
** move_key
*/

# define BACKSPACE	127
# define DEL		"\e[3~"
# define LEFT_ARR	"\e[D"
# define RIGHT_ARR	"\e[C"
# define HOME		"\e[H"
# define END		"\e[F"
# define CTRL_LEFT	"\e[1;5D"
# define CTRL_RIGHT	"\e[1;5C"
# define CTRL_UP	"\e[1;5A"
# define CTRL_DOWN	"\e[1;5B"

/*
** shift_key
*/

# define SHIFT_LFT  "\e[1;2D"
# define SHIFT_RGT  "\e[1;2C"
# define SHIFT_UP   "\e[1;2A"
# define SHIFT_DO   "\e[1;2B"

/*
** hist_key
*/

# define UP_ARR		"\e[A"
# define DOWN_ARR	"\e[B"

/*
** color signal key
*/

# define SET_COLOR	7
# define SET_SIG	8

/*
** copy cut paste clear
*/

# define CTRL_L		12
# define CTRL_K		'\v'

/*
** autocomplition
*/

# define TAB		9

#endif
