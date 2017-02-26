#include "def.h"

#ifndef __PRINT_H__
#define __PRINT_H__

void print_game(const Board * );
Point input(char * prompt);
Move user_move(const Board * b, char turn);

void print_point(const Point p);
void print_move(const Move m);

#endif