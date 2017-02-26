#ifndef __DEF_H__
#define __DEF_H__

#define PLACES_AVAILABLE 25

#define ROW 5
#define COL 5

/*
	change the levels from  here
	Use even digit 2,4,6,8
	> 8 costs too much time
*/
#define MAXLEVEL 8

#define NEIGHBOUR_COUNT 8

#define TIGER_COUNT 4
#define GOAT_COUNT_MAX 20

/*
	adjust:
	how many goats should be dead to declare tiger as winner
*/
#define DEAD_GOAT_MAX 5

#define GOAT 'o'
#define TIGER 'X'
#define EMPTY ' '

/*different scores for Moves*/
#define EAT_MOVE 6 //highest score
#define TIGHT_TRAP 5 //only available Move for goat is inside trap
#define FOLLOW 4 //
#define MAKE_TRAP 3 //
#define VMOVE 1 //valid move
#define OCCUPY 0 //goats occupying boundary


typedef enum {False,True} boolean;

typedef struct {
    int x;
    int y;
} Point;



typedef struct {
	char piece;
	
	/*
		These were planned for optimizations-not used 
		more implementation regarding this is needed.
	*/
	boolean engaged;

}Piece;

typedef struct alu {
	int goats_in_hand;
	int goats_eaten;
	Piece ** pieces;

	/******For evaluations**************************/
	//Point of tigers - updated regularly
	Point * tiger_pos;

	//Points that are rooms
	Point * rooms;
	int rooms_count;
	int rooms_size;

	//to check the number of goats by the latest move
	int prev_goat_count;

	//to check if already analyzed board position is found
	/*
		currently these are not used - will be used in coming version
		it is better to make the database/library of the moves 
		after analyzing the board positions
	*/
	/*
	char ** analyzed_boards;
	int ab_count;
	int ab_size;
	int prev ;
	*/
} Board;

typedef struct{
	Point from;
	Point to;
	/*
		currently this is not used
	*/
	int score; //heuristic score for this move
	boolean attack_info; //this becomes true if the move is for tigers and attack move
	int score_depth;//debug
} Move;


#endif
