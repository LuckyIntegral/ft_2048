/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:37:36 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/11 17:22:32 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wong_kar_wai.h"

int received_signal = 0;

static void resizeHandler(int sig)
{
	if (sig == SIGWINCH)
	{
		received_signal = SIGWINCH;
	}
}

static WINDOW	*init(void)
{
	int width = 0, height = 0;

	WINDOW *main_window = initscr();	// initialize ncurses and create a window
	signal(SIGWINCH, resizeHandler);	// handle window resize
	setlocale(LC_ALL, "");				// now we can use unicode
	noecho(); 							// don't echo any keypresses
	keypad(stdscr, TRUE); 				// enable special keys like arrow keys
	curs_set(0); 						// hide the cursor
	nodelay(main_window, TRUE);			// make getch non-blocking
	start_color();						// enable colors
	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	getmaxyx(main_window, height, width);
	if (height < MIN_HEIGHT || width < MIN_WIDTH)
	{
		endwin();
		printf("Please resize the window to at least 20x10\n");
		exit(1);
	}

	return (main_window);
}

static void display_options(WINDOW *main_window, int option)
{
	int width = 0, height = 0;

	clear();
	box(main_window, 0, 0);
	getmaxyx(main_window, height, width);
	mvprintw(height / 2 - 1, width / 2 - 8, "Select game mode:");

	if (option == 3)
		attron(A_REVERSE);
	mvprintw(height / 2, width / 2 - 2, "3x3");
	attroff(A_REVERSE);

	if (option == 4)
		attron(A_REVERSE);
	mvprintw(height / 2 + 1, width / 2 - 2, "4x4");
	attroff(A_REVERSE);

	if (option == 5)
		attron(A_REVERSE);
	mvprintw(height / 2 + 2, width / 2 - 2, "5x5");
	attroff(A_REVERSE);

	refresh();
}

int input_listener(int *selected)
{
	timeout(1000);
	int ch = getch();

	if (ch == 10 || ch == 'q')
	{
		return (SELECTED);
	}
	else if (ch == KEY_UP)
	{
		*selected = (*selected - 1) > 2 ? *selected - 1 : 5;
	}
	else if (ch == KEY_DOWN)
	{
		*selected = (*selected + 1) < 6 ? *selected + 1 : 3;
	}
	return (NOT_SELECTED);
}

int select_menu(void)
{
	int selected = 4;
	WINDOW *main_window = init();
	endwin();
	main_window = init();
	display_options(main_window, selected);

	while (1)
	{
		if (received_signal == SIGWINCH)
		{
			endwin();
			main_window = init();
			received_signal = 0;
		}
		if (input_listener(&selected) == SELECTED)
		{
			break;
		}
		else
		{
			display_options(main_window, selected);
		}
	}
	endwin();
	return (selected);
}
