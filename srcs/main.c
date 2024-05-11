/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:16:02 by vfrants           #+#    #+#             */
/*   Updated: 2024/05/11 13:37:25 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wong_kar_wai.h"

int board[SIZE][SIZE];

void initialize() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard() {
    int i, j;
    printf("+----+----+----+----+\n");
    for (i = 0; i < SIZE; i++) {
        printf("|");
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("    |");
            } else {
                switch(board[i][j]) {
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
        printf("+----+----+----+----+\n");
    }
}

int isFull() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void generateNumber() {
    if (!isFull()) {
        int i, j;
        do {
            i = rand() % SIZE;
            j = rand() % SIZE;
        } while (board[i][j] != 0);
        int value = (rand() % 10 == 0) ? 4 : 2;
        board[i][j] = value;
    }
}

int moveLeft() {
    int i, j, moved = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == 0 && board[i][j + 1] != 0) {
                board[i][j] = board[i][j + 1];
                board[i][j + 1] = 0;
                moved = 1;
            }
        }
    }
    return moved;
}

void mergeLeft() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1] && board[i][j] != 0) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
}

void shiftLeft() {
    while (moveLeft()) {}
    mergeLeft();
    moveLeft();
}

void rotateBoardClockwise() {
    int i, j, temp;
    for (i = 0; i < SIZE / 2; i++) {
        for (j = i; j < SIZE - i - 1; j++) {
            temp = board[i][j];
            board[i][j] = board[SIZE - 1 - j][i];
            board[SIZE - 1 - j][i] = board[SIZE - 1 - i][SIZE - 1 - j];
            board[SIZE - 1 - i][SIZE - 1 - j] = board[j][SIZE - 1 - i];
            board[j][SIZE - 1 - i] = temp;
        }
    }
}

void moveAndMerge(char direction) {
    switch (direction) {
        case 'S':
        case 's':
            rotateBoardClockwise();
            shiftLeft();
            rotateBoardClockwise();
            rotateBoardClockwise();
            rotateBoardClockwise();
            break;
        case 'A':
        case 'a':
            shiftLeft();
            break;
        case 'D':
        case 'd':
            rotateBoardClockwise();
            rotateBoardClockwise();
            shiftLeft();
            rotateBoardClockwise();
            rotateBoardClockwise();
            break;
        case 'W':
        case 'w':
            rotateBoardClockwise();
            rotateBoardClockwise();
            rotateBoardClockwise();
            shiftLeft();
            rotateBoardClockwise();
            break;
        default:
            printf("Invalid move! Please try again.\n");
    }
}

int gameOver() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == WIN_VALUE) {
                return 1;
            }
        }
    }
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
            if ((i < SIZE - 1 && board[i][j] == board[i + 1][j]) ||
                (j < SIZE - 1 && board[i][j] == board[i][j + 1])) {
                return 0;
            }
        }
    }
    return -1;
}

int main() {
    srand(time(NULL));
    initialize();
    generateNumber();
    generateNumber();
    printBoard();
    while (1) {
        char userInput;
        printf("Enter your move (W - Up, A - Left, S - Down, D - Right): ");
        scanf(" %c", &userInput);
        moveAndMerge(userInput);
        if (gameOver() == 1) {
            printf("Congratulations! You win!\n");
            break;
        } else if (gameOver() == -1) {
            printf("Game over! You lose!\n");
            break;
        } else {
            generateNumber();
            printBoard();
        }
    }
    return 0;
}
