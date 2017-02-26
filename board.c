#include "debug_def.h"
#include "def.h"
#include "board.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
Board * initialize_board(){
    int i,j;

	Board * board = (Board*)malloc(sizeof(Board));
	board->pieces = (Piece**)malloc(ROW*sizeof(Piece*));

    for(i=0;i<ROW;i++){
        board->pieces[i] = (Piece*)malloc(COL*sizeof(Piece));
    }

	board->tiger_pos = (Point*)malloc(sizeof(Point)*TIGER_COUNT);//4 tigers

	board->rooms_size = 5;
	board->rooms_count = 0;
	board->rooms = (Point*)malloc(sizeof(Point)*board->rooms_size);


	/*
		analyzed board - disabled for now - maybe database/library added later
	*/

	/*
	board->ab_count = 0; //analyzed board
	board->ab_size = 500000;

	board->analyzed_boards = (char**)malloc(board->ab_size * sizeof(char*));
	if(board->analyzed_boards == NULL){
		printf("Memery not allocated for the analyzed board positions BOARD::INITIALIZE\n");
		//getchar();
	}
	for(i=0;i<board->ab_size;i++){
		board->analyzed_boards[i] = NULL;
	}
	*/

	board->goats_eaten = 0;
	board->goats_in_hand = 20;
	board->prev_goat_count = 0;

    for(i=0;i<ROW;i++){
        for(j=0;j<COL;j++){
            board->pieces[i][j].piece = EMPTY;
        }
    }


/*
  The following code is the different board setup
    used for testing
*/
#define __EMPTY__
//#define __NINETEEN__
//#define __SEVENTEEN__
//#define __NINETEEN__
//#define __NINETEEN_EATEN__
//#define __FULL__
//#define __HALF__
//#define __ERROR1__
//#define __TWIN__ //tiger win


#ifdef __EMPTY__
	//requires goats to move first
  board->pieces[0][0].piece=TIGER;
	board->pieces[4][0].piece=TIGER;
	board->pieces[0][4].piece=TIGER;
	board->pieces[4][4].piece=TIGER;
#endif

#ifdef __SEVENTEEN__
	//requires tiger to move first
    board->pieces[4][0].piece=TIGER;
	board->pieces[1][2].piece=TIGER;
	board->pieces[1][3].piece=TIGER;
	board->pieces[3][2].piece=TIGER;

	board->pieces[0][0].piece=GOAT;
	board->pieces[1][0].piece=GOAT;
	board->pieces[2][0].piece=GOAT;
	board->pieces[2][1].piece=GOAT;
	board->pieces[0][1].piece=GOAT;
	board->pieces[0][2].piece=GOAT;
	board->pieces[0][3].piece=GOAT;
	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;
	board->pieces[4][3].piece=GOAT;
	board->pieces[4][2].piece=GOAT;
	board->pieces[4][1].piece=GOAT;
	board->pieces[3][1].piece=GOAT;
	board->pieces[2][2].piece=GOAT;

	board->goats_in_hand = 3;
#endif


//requires tigers to move first
#ifdef __NINETEEN__
    board->pieces[1][2].piece=TIGER;
	board->pieces[2][2].piece=TIGER;
	board->pieces[2][3].piece=TIGER;
	board->pieces[2][4].piece=TIGER;

	board->pieces[0][0].piece=GOAT;
	board->pieces[1][0].piece=GOAT;
	board->pieces[2][0].piece=GOAT;
	board->pieces[3][0].piece=GOAT;
	board->pieces[4][0].piece=GOAT;

	board->pieces[1][1].piece=GOAT;
	board->pieces[2][1].piece=GOAT;
	board->pieces[3][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;

	board->pieces[0][2].piece=GOAT;
	board->pieces[3][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[0][3].piece=GOAT;
	board->pieces[3][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 0;
	board->goats_eaten = 1;
#endif

//requires tigers to move first
#ifdef __NINETEEN_EATEN__
    board->pieces[0][2].piece=TIGER;
	board->pieces[1][2].piece=TIGER;
	board->pieces[2][3].piece=TIGER;
	board->pieces[3][3].piece=TIGER;

	board->pieces[0][0].piece=GOAT;
	board->pieces[1][0].piece=GOAT;
	board->pieces[2][0].piece=GOAT;
	board->pieces[3][0].piece=GOAT;
	board->pieces[4][0].piece=GOAT;

	board->pieces[0][1].piece=GOAT;
	board->pieces[1][1].piece=GOAT;
	board->pieces[2][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;


	board->pieces[2][2].piece=GOAT;
	board->pieces[3][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[0][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 0;
	board->goats_eaten = 1;
#endif


//requires tigers to move first
#ifdef __FULL__
    board->pieces[0][2].piece=TIGER;
	board->pieces[1][2].piece=TIGER;
	board->pieces[2][2].piece=TIGER;
	board->pieces[1][3].piece=TIGER;

	board->pieces[0][0].piece=GOAT;
	board->pieces[1][0].piece=GOAT;
	board->pieces[2][0].piece=GOAT;
	board->pieces[3][0].piece=GOAT;
	board->pieces[4][0].piece=GOAT;

	board->pieces[0][1].piece=GOAT;
	board->pieces[1][1].piece=GOAT;
	board->pieces[2][1].piece=GOAT;
	board->pieces[3][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;

	board->pieces[3][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[0][3].piece=GOAT;
	board->pieces[3][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 0;
#endif

#ifdef __HALF__
	//requires tigers to move first
    board->pieces[0][0].piece=TIGER;
	board->pieces[1][3].piece=TIGER;
	board->pieces[2][2].piece=TIGER;
	board->pieces[1][4].piece=TIGER;

	board->pieces[1][0].piece=GOAT;
	board->pieces[2][0].piece=GOAT;
	board->pieces[3][0].piece=GOAT;
	board->pieces[4][0].piece=GOAT;

	board->pieces[0][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;

	board->pieces[0][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[0][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 6;
	board->goats_eaten = 0;
#endif

//fixed
#ifdef __ERROR1__
    board->pieces[0][0].piece=TIGER;
	board->pieces[1][2].piece=TIGER;
	board->pieces[1][3].piece=TIGER;
	board->pieces[2][3].piece=TIGER;

	board->pieces[2][0].piece=GOAT;
	board->pieces[4][0].piece=GOAT;

	board->pieces[0][1].piece=GOAT;
	board->pieces[1][1].piece=GOAT;
	board->pieces[2][1].piece=GOAT;
	board->pieces[3][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;

	board->pieces[0][2].piece=GOAT;
	board->pieces[2][2].piece=GOAT;
	board->pieces[3][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[0][3].piece=GOAT;
	board->pieces[3][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 0;
	board->goats_eaten = 1;
#endif

#ifdef __TWIN__
    board->pieces[0][0].piece=TIGER;
	board->pieces[3][0].piece=TIGER;
	board->pieces[0][3].piece=TIGER;
	board->pieces[1][2].piece=TIGER;

	board->pieces[4][0].piece=GOAT;

	board->pieces[2][1].piece=GOAT;
	board->pieces[3][1].piece=GOAT;
	board->pieces[4][1].piece=GOAT;

	board->pieces[2][2].piece=GOAT;
	board->pieces[3][2].piece=GOAT;
	board->pieces[4][2].piece=GOAT;

	board->pieces[1][3].piece=GOAT;
	board->pieces[2][3].piece=GOAT;
	board->pieces[3][3].piece=GOAT;
	board->pieces[4][3].piece=GOAT;

	board->pieces[0][4].piece=GOAT;
	board->pieces[1][4].piece=GOAT;
	board->pieces[2][4].piece=GOAT;
	board->pieces[3][4].piece=GOAT;
	board->pieces[4][4].piece=GOAT;

	board->goats_in_hand = 0;
	board->goats_eaten = 4;
#endif

	return board;
}

void destroy_board(Board * board){
	int i;
	free(board->rooms);
	free(board->tiger_pos);

    for(i=0;i<ROW;i++){
        free(board->pieces[i]);
    }

	free(board->pieces);
	free(board);
	board = NULL;
}

/*
	Copies the board position including turn to charactor array
	first element refers to turn.
	Optimization possible
*/
/*
char * copy(const Board * board, char turn){
	int i,j,count=0;
	char * ret = (char*)malloc(sizeof(char)*27);
	if(ret==NULL){
		printf("I need more memory: Board::copy\n ");
	}
	ret[count++] = turn;
	for(i=0;i<COL;i++){
        for(j=0;j<ROW;j++){
            ret[count++] = board->pieces[i][j].piece;
        }
    }
	ret[count] = '\0';
	return ret;
}
*/
/*
	to store the analyzed board positions and turn
*/
/*
//modification in Board structure needed
void store_state(Board *board, char * state){
	static int d;
	int i;
	if(board->ab_count == board->ab_size){
		printf("%d for states not enough Board::store_state\n");
		//getchar(); //just to check
		for(i=0;i<board->ab_size;i++){
			free(board->analyzed_boards[i]);
			board->analyzed_boards[i] = NULL;
		}
		board->ab_count = 0;
	}

	if(board->ab_count < board->ab_size){
		board->analyzed_boards[board->ab_count++] = state;
	}else{
		d++;
		if(d%10000 == 0){
			printf("%d\n",d);
		}
	}
}
*/
/*
	testing if certain board positions analyzed already or not
	support for hash-table will be needed later in improved version
	very very bad now.
*/
/*
//modification in board structure needed
boolean analyzed(Board * board, char * state){
	int i;
	for(i=0;i<board->ab_count;i++){
		if(strcmp(board->analyzed_boards[i],state)==0){
			return True;
		}
	}
	return False;
}
*/
Point scalar_mul(Point p, int factor){
	return new_point(p.x*factor, p.y*factor);
}

Point scalar_div(Point p, int factor){
	return new_point(p.x/factor, p.y/factor);
}


boolean is_goat(const Board * board, const Point p){
	if(board->pieces[p.x][p.y].piece==GOAT)
		return True;
	return False;
}

boolean is_tiger(const Board * board, const Point p){
	if(board->pieces[p.x][p.y].piece==TIGER)
		return True;
	return False;
}

boolean is_empty(const Board * board, const Point p){
	if(is_inside(p)){
	if(board->pieces[p.x][p.y].piece==EMPTY)
		return True;}
	return False;
}
static boolean is_first_20(Point p){
	return p.x == -2? True:False;
}

void put(Board * b, Point p){
	b->pieces[p.x][p.y].piece= GOAT;
}

/*put piece (pieces)*/
void put_ps(Board * b, Point p, char piece){
	b->pieces[p.x][p.y].piece= piece;
}



void clear(Board * b, Point p){
	b->pieces[p.x][p.y].piece= EMPTY;
}

/*
	board : Baghchal Board
	m:	move

*/
void execute_move(Board * board, Move m){
	if(is_first_20(m.from)){
		put(board,m.to);
		board->goats_in_hand--;
		return;
	}

	/*
		this value will be checked in scoring
		function to test if the move was eating move
		(== highest priority) or not

	*/
	board->prev_goat_count = board->goats_eaten;

	/*Computer Player*/
	if(m.attack_info){
		Point mp = mid_point(m.from,m.to);



		#ifdef _DEBUG
		if(!is_goat(board,mp)){
			printf("**Error from execute move**");
		}
		#endif

		board->pieces[mp.x][mp.y].piece= EMPTY;
		board->goats_eaten++;
	}
	/*Two Player--testing*/
	if(is_jump_possible(board,m.from,m.to)){
		Point mp = mid_point(m.from,m.to);
		board->pieces[mp.x][mp.y].piece= EMPTY;
		board->goats_eaten++;
	}

	board->pieces[m.to.x][m.to.y].piece= board->pieces[m.from.x][m.from.y].piece;
	board->pieces[m.from.x][m.from.y].piece= EMPTY;
}


void undo_move(Board * board, Move m){
	if(is_first_20(m.from)){
		clear(board,m.to);
		board->goats_in_hand++;
		return;
	}

	if(m.attack_info){
		Point mp = mid_point(m.from,m.to);
		board->pieces[mp.x][mp.y].piece= GOAT;
		board->goats_eaten--;
	}


	board->pieces[m.from.x][m.from.y].piece= board->pieces[m.to.x][m.to.y].piece;
	board->pieces[m.to.x][m.to.y].piece= EMPTY;
}

Point mid_point(const Point from, const Point to){
	Point mid;
	mid.y = (from.y+to.y)/2;
	mid.x = (from.x+to.x)/2;
	return mid;
}

boolean is_same_point(const Point p1, const Point p2){
	if(p1.x == p2.x && p1.y == p2.y) return True;
	return False;
}
boolean is_same_move(const Move m1, const Move m2){
	if(is_same_point(m1.from,m2.from) && is_same_point(m1.to,m2.to))
		return True;
	return False;
}

int distance_between(const Point from, const Point to){
	int xdiff,ydiff;
	Point p,diff,factor;

	if(from.x == to.x) return abs(from.y - to.y);
	if(from.y == to.y) return abs(from.x - to.x);

	xdiff = abs(from.x - to.x);
	ydiff = abs(from.y - to.y);

	if(xdiff == ydiff){
		switch(xdiff){
		case 1:
			if(does_link_exist(from,to))
				return xdiff;
			break;
		case 2:
			p = mid_point(from,to);
			if(are_adj_points(from,p) && are_adj_points(to,p))
				return xdiff;
			break;
		case 3:
			diff = subtraction(from,to);
			factor = scalar_div(diff,3);
			if(does_link_exist(from,addition(from,factor)) && does_link_exist(subtraction(factor,to),to))
				return xdiff;
			break;
		case 4:
			return xdiff; //maximum possible end-end diagonal or horizontol or vertical
		default:
			break;
		}
	}
	/*do not return valid distance if link does not exist*/
	return 5;
}

boolean does_link_exist(const Point a, const Point b){
	if((a.x * 5 + a.y)%2 && (b.x * 5 + b.y)%2)
		return False;
	return True;
}

boolean are_adj_points(const Point a, const Point b){
	return distance_between(a,b)==1? True:False;
}

boolean are_diagonal_points(const Point a, const Point b){
	int xdiff = abs(a.x - b.x);
	int ydiff = abs(a.y - b.y);

	if(xdiff == ydiff) return True;
	else return False;
}

boolean are_vertical_points(const Point a, const Point b){
	if(a.x == b.x) return True;
	return False;
}

boolean are_horizontal_points(const Point a, const Point b){
	if(a.y == b.y) return True;
	return False;
}


/*applicable for tiger only*/
boolean is_jump_possible(const Board *board, const Point a, const Point b){

	if( is_tiger(board,a) && is_empty(board,b) &&
		distance_between(a,b) == 2 && is_goat( board, mid_point( a, b)) ){
		return True;
	}
	return False;
}

boolean is_inside(const Point p){
	if(p.x < 0 || p.x > 4 || p.y < 0 || p.y > 4)
		return False;
	return True;
}

int get_dead_goat_count(const Board * board){
	return board->goats_eaten;
}

int get_goat_in_hand_count(const Board * board){
	return board->goats_in_hand;
}

void update_rooms(Board * board, const Point * neighbours){
	int i,j,k;
	Point p,p1,p2;
	boolean t;

	board->rooms_count = 0;
	//print_game(board);

	for(i=0;i<COL;i++){
		for(j=0;j<ROW;j++){
			p = new_point(i,j);
			if(is_empty(board,p)){

				t = True;
				for(k=0;k<NEIGHBOUR_COUNT;k++){

					p1 = addition(p,neighbours[k]);
					p2 = addition(p,scalar_mul(neighbours[k],2));
					if( is_inside( p1 ) && are_adj_points(p,p1)){
						if(! is_goat(board,p1)){
							t = False;
							break;
						}
						if( is_inside( p2 )){
							if(! is_goat(board,p1)){
								t = False;
								break;
							}
						}
					}
				}

				if(t){
					board->rooms[board->rooms_count++] = p;
				}
			}
		}
	}
}

Point new_point(int x, int y){
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

Move new_move(Point from, Point to,boolean attack_info){
	Move m;
	m.from = from;
	m.to = to;
	m.attack_info = attack_info;
	return m;
}

Point addition(const Point p1,const Point p2){
	return new_point(p1.x+p2.x,p1.y+p2.y);
}

Point subtraction(const Point p1,const Point p2){
	return new_point(p2.x-p1.x,p2.y-p1.y);
}

char who(const Board * b, const Point p){
	return b->pieces[p.x][p.y].piece;
}

void engage(Board * board, Point p){
	board->pieces[p.x][p.y].engaged = True;
}

void unengage(Board * board, Point p){
	board->pieces[p.x][p.y].engaged = False;
}


void update_tiger_pos(Board * b){
	int i,j,index=0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			Point p = new_point(i,j);
			if(is_tiger(b,p)){
				//unengage(b,p); //if they are engaged clear; will be re-evaluated from evaluation function
				b->tiger_pos[index++] = p;
			}
		}
	}
}


boolean is_empty_between(Board * board, const Point p1, const Point p2, int distance){
	Point tmp, factor;
	int i;
	tmp = subtraction(p2,p1);
	factor = scalar_div(tmp,distance);
	tmp = p2;
	for(i=1;i<distance;i++){
		tmp = addition(tmp,factor);
		if(is_inside(tmp) && ! is_empty(board,tmp)){
			return False;
		}
	}
	return True;
}
