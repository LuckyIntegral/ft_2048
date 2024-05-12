/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:34:40 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/12 14:07:37 by tkafanov         ###   ########.fr       */
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

# define ERROR_SMALL_SCREEN "Please resize the window to at least 99x29\n"
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
