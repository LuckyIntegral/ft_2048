/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wong_kar_wai.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:34:40 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/11 14:28:27 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WONG_KAR_WAI_H
# define WONG_KAR_WAI_H

# include "../libft/libft.h"

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# ifndef SIZE
#  define SIZE 4
# endif

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

typedef enum e_direction
{
    GAME_WON,
    GAME_LOST,
    GAME_CONTINUE,
}	t_direction;

#endif // WONG_KAR_WAI_H
