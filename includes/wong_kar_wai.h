/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:34:40 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/12 02:37:57 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WONG_KAR_WAI_H
# define WONG_KAR_WAI_H

# include "../libft/libft.h"

# include <ncurses.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <locale.h>
# include <stdio.h>
# include <time.h>

# ifndef SIZE
#  define SIZE 4
# endif

# define MENU_MIN_WIDTH 39
# define MENU_MIN_HEIGHT 19
# define GRID_THREE_MIN_WIDTH 39
# define GRID_THREE_MIN_HEIGHT 19
# define GRID_FOUR_MIN_WIDTH 83
# define GRID_FOUR_MIN_HEIGHT 27
# define GRID_FIVE_MIN_WIDTH 163
# define GRID_FIVE_MIN_HEIGHT 33

enum e_const
{
    WIN_VALUE = 2048
};

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_WHITE   "\x1b[37m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# define KEY_ESC 27

typedef unsigned long long int  t_score;

typedef enum e_number_len
{
    SIZE_THREE = 3,
    SIZE_FOUR = 5,
    SIZE_FIVE = 8,
}  t_number_len;

typedef enum e_status
{
    GAME_WON,
    GAME_LOST,
    GAME_CONTINUE,
}	t_status;

typedef enum e_selection
{
    SELECTED,
    NOT_SELECTED,
}	t_selection;

extern int  received_signal;

void    print_board(WINDOW *win, const int size,
            int board[size][size], const int nbr_len, t_score score);
bool    move_and_merge(int direction, int size,
            int board[size][size], t_score *score);
void    rotate_board_clockwise(int size, int board[size][size]);
void    generate_number(int size, int board[size][size]);
int     game_over(int size, int board[size][size]);
void    resize_handler(int sig);
int     select_menu(void);
WINDOW  *init(void);

#endif // WONG_KAR_WAI_H
