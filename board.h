
#ifndef __DATA_H__
#define __DATA_H__

/*
	New Board setup
	returns empty board
*/
Board * initialize_board();

/*
	Checks if there exists a way from point a to point b
	a : location (Co ordinate)
	b : location (Co ordinate)
	return : True (if exists way) False otherwise
*/
boolean are_adj_points(const Point a, const Point b);
/*
	Checks if there exists a way from point a to point b
	a : location (Co ordinate)
	b : location (Co ordinate)
	return : True (if exists way) False otherwise
*/
boolean are_diagonal_points(const Point a, const Point b);

/*
	works as name suggests
*/

boolean are_horizontal_points(const Point a, const Point b); //are on same horizontol line
boolean are_vertical_points(const Point a, const Point b); // are on same vertical line

/*
	if there were a piece in point a, can it then be moved to point b - is there a line between points
*/
boolean does_link_exist(const Point a, const Point b);

/*
	checking if Points p1 and p2 are on one single line, is there any pieces in between
*/
boolean is_empty_between(Board * board, const Point p1, const Point p2, int distance);

/*
	is a Point p empty
*/
boolean is_empty(const Board * board, const Point p); 
/*
	is there a goat in Point p
*/
boolean is_goat(const Board * board, const Point p); 
/*
	is Point p a valid point - does it reside inside the board
*/
boolean is_inside(const Point p);
/*
	is a tiger move possible from Point a to Point b
*/
boolean is_jump_possible(const Board * board, const Point a, const Point b);
/*
	is co-ordinate of p1 and p2 same?
*/
boolean is_same_point(const Point p1, const Point p2);
/*
	checking if "from" and "to" of m1 and m2 same?
*/
boolean is_same_move(const Move m1, const Move m2);
/*
	is there a tiger in Point p
*/
boolean is_tiger(const Board * board, const Point p);

/*
	returns wther TIGER or GOAT - a character basically	
*/
char who(const Board * board, const Point p);
/*
	stores the board information on character string of length 27
*/
char * copy(const Board * board, char turn);

/*
	returns true if board state was already analyzed
*/
boolean analyzed(Board * board, char * state);
/*
	calculates the distance between two points--returns the number of steps
	that needs to be walked to reach from Point "from" to Point "to"
	not pythagorean theorem
*/
int distance_between(const Point from, const Point to);
/*
	returns the number of dead goats
*/
int get_dead_goat_count(const Board * board);
/*
	returns the number of goats in hand
*/
int get_goat_in_hand_count(const Board * board);
/*
	returns a Move from given parameter - abstraction
*/
Move new_move(Point from, Point to, boolean attack_info);
/*
	returns mid-point Between Points "a" and "b"
*/
Point mid_point(const Point a, const Point b);
/*
	returns a Point from given parameters
*/
Point new_point(int x, int y);
/*
	returns a point by adding x-part and y-part of p1 and p2
*/
Point addition(const Point p1,const Point p2);
/*
	returns a point by subtracting x-part and y-part from p2 and p1
*/
Point subtraction(const Point p1,const Point p2);
/*
	multiply the given point's x and y by factor
*/
Point scalar_mul(Point p,int factor);
/*
	divide the given point's x andn y by factor.
*/
Point scalar_div(Point p,int factor); 
/*
	Replaces the Point p of Board board b  by ' ' -- makes empty
*/
void clear(Board * board, Point p);
/*
	return the memory
*/
void destroy_board(Board * board);
/*
	performs Move m on Board board	
*/
void execute_move(Board * board, Move m);
/*
	puts a goat on Point p of Board board
*/
void put(Board * board, Point p);
/*
	works as put but which piece to put should be specified.
*/
void put_ps(Board * board, Point p, char piece);
/*
	stores the board state (stored as character string) to memory
*/
void store_state(Board *board, char * state);
/*
	undos the Move m on Board b
*/
void undo_move(Board * board, Move m);
/*
	Sets a piece to be engaged - not prefarable to move if engaged
	not in use
*/
void engage(Board * board, Point p);
/*
	clears the engage flag
*/
void unengage(Board * board, Point p);
/*
	tracks the location of tigers
*/
void update_tiger_pos(Board * board);
/*
	if a free room is made by goats, count them--key to goat's win
*/
void update_rooms(Board * board, const Point * neighbours);

#endif