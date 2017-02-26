#include "list.h"
#ifndef __EVALUATION_H__
#define __EVALUATION_H__
/*
	Generate move for a Side 'turn' from Point 'from' on Board 'board'
*/
List get_moves(const Board * board, char turn, Point from);
/*
	Generate all legal moves for Side turn
*/
List generate_moves(const Board * board, char turn);
/*
	checks if terminal state / end of the game position is reached
*/
boolean is_game_over(const Board * board, char turn, List * moves);
/*
	checks if any traps exists on the board
*/
int check_trap(Board * board);
/*
	calculate the score for the board
*/
int static_score(Board * board);

#endif