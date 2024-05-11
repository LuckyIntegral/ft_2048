/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:28:52 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/11 15:52:13 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wong_kar_wai.h"
#include <ncurses.h>
#include <stdio.h>

void initialize(int size, int board[size][size])
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			board[i][j] = 0;
		}
	}
}

void print_board(int size, int board[size][size])
{
	int i, j;
	if (size == 3)
		printf("+----+----+----+\n");
	if (size == 4)
		printf("+----+----+----+----+\n");
	if (size == 5)
		printf("+----+----+----+----+----+\n");
	for (i = 0; i < size; i++)
	{
		printf("|");
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == 0)
			{
				printf("    |");
			}
			else
			{
				switch(board[i][j])
				{
					case 2:
						printf(ANSI_COLOR_RED);
						break;
					case 4:
						printf(ANSI_COLOR_GREEN);
						break;
					case 8:
						printf(ANSI_COLOR_YELLOW);
						break;
					case 16:
						printf(ANSI_COLOR_BLUE);
						break;
					case 32:
						printf(ANSI_COLOR_MAGENTA);
						break;
					case 64:
						printf(ANSI_COLOR_CYAN);
						break;
					case 128:
						printf(ANSI_COLOR_WHITE);
						break;
					case 256:
						printf(ANSI_COLOR_RED);
						break;
					case 512:
						printf(ANSI_COLOR_GREEN);
						break;
					case 1024:
						printf(ANSI_COLOR_YELLOW);
						break;
					case 2048:
						printf(ANSI_COLOR_BLUE);
						break;
					default:
						printf(ANSI_COLOR_RESET);
						break;
				}
				printf("%4d", board[i][j]);
				printf(ANSI_COLOR_RESET);
				printf("|");
			}
		}
		printf("\n");
		if (size == 3)
			printf("+----+----+----+\n");
		if (size == 4)
			printf("+----+----+----+----+\n");
		if (size == 5)
			printf("+----+----+----+----+----+\n");
	}
}

int is_full(int size, int board[size][size])
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

void generate_number(int size, int board[size][size])
{
	if (!is_full(size, board))
	{
		int i, j;
		do
		{
			i = rand() % size;
			j = rand() % size;
		} while (board[i][j] != 0);
		int value = (rand() % 10 == 0) ? 4 : 2;
		board[i][j] = value;
	}
}

bool move_left(int size, int board[size][size])
{
	int i, j;
	bool moved = true;
	bool res = false;
	while (moved)
	{
		moved = false;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size - 1; j++)
			{
				if (board[i][j] == 0 && board[i][j + 1] != 0)
				{
					board[i][j] = board[i][j + 1];
					board[i][j + 1] = 0;
					moved = true;
					res = true;
				}
			}
		}
	}
	return res;
}

bool merge_left(int size, int board[size][size])
{
	bool res = false;
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - 1; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j] != 0)
			{
				board[i][j] *= 2;
				board[i][j + 1] = 0;
				res = true;
			}
		}
	}
	return res;
}

bool shift_left(int size, int board[size][size])
{
	bool first, second, third;
	first = move_left(size, board);
	second = merge_left(size, board);
	third = move_left(size, board);
	return first || second || third;
}

void rotate_board_clockwise(int size, int board[size][size])
{
	int i, j, temp;
	for (i = 0; i < size / 2; i++)
	{
		for (j = i; j < size - i - 1; j++)
		{
			temp = board[i][j];
			board[i][j] = board[size - 1 - j][i];
			board[size - 1 - j][i] = board[size - 1 - i][size - 1 - j];
			board[size - 1 - i][size - 1 - j] = board[j][size - 1 - i];
			board[j][size - 1 - i] = temp;
		}
	}
}

bool move_and_merge(char direction, int size, int board[size][size])
{
	bool res = false;
	switch (direction)
	{
		case 'S':
		case 's':
			rotate_board_clockwise(size, board);
			res = shift_left(size, board);
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			break;
		case 'A':
		case 'a':
			res = shift_left(size, board);
			break;
		case 'D':
		case 'd':
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			res = shift_left(size, board);
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			break;
		case 'W':
		case 'w':
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			rotate_board_clockwise(size, board);
			res = shift_left(size, board);
			rotate_board_clockwise(size, board);
			break;
		default:
			printf("Invalid move! Please try again.\n");
	}
	return res;
}

int game_over(int size, int board[size][size])
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == WIN_VALUE)
			{
				return GAME_WON;
			}
		}
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (board[i][j] == 0)
			{
				return GAME_CONTINUE;
			}
			if ((i < size - 1 && board[i][j] == board[i + 1][j]) ||
				(j < size - 1 && board[i][j] == board[i][j + 1]))
				{
				return GAME_CONTINUE;
			}
		}
	}
	return GAME_LOST;
}

int init()
{
	// srand(time(NULL));
	// initialize();
	// generateNumber();
	// generateNumber();
	// printBoard();
	// while (1)
	// {
	// 	char userInput;
	// 	printf("Enter your move (W - Up, A - Left, S - Down, D - Right): ");
	// 	scanf(" %c", &userInput);
	// 	moveAndMerge(userInput);
	// 	if (gameOver() == GAME_WON)
	// 	{
	// 		printf("Congratulations! You win!\n");
	// 		return 0;
	// 	}
	// 	else if (gameOver() == GAME_LOST)
	// 	{
	// 		printf("Game over! You lose!\n");
	// 		return 0;
	// 	}
	// 	else
	// 	{
	// 		generateNumber();
	// 		printBoard();
	// 	}
	// }
	return 1;
}

int main()
{
	int size = 5;
	int board[size][size];
	bool moved = false;

	srand(time(NULL));
	initialize(size, board);
	generate_number(size, board);
	generate_number(size, board);
	print_board(size, board);
	while (1)
	{
		char userInput;
		printf("Enter your move (W - Up, A - Left, S - Down, D - Right): ");
		scanf(" %c", &userInput);
		moved = move_and_merge(userInput, size, board);
		if (game_over(size, board) == GAME_WON)
		{
			printf("Congratulations! You win!\n");
			break;
		}
		else if (game_over(size, board) == GAME_LOST)
		{
			printf("Game over! You lose!\n");
			break;
		}
		else if (moved)
		{
			generate_number(size, board);
			print_board(size, board);
			moved = false;
		}
	}
	return 0;
}
