#include "debug_def.h"
#include "def.h"
#include "board.h"
#include "io.h"
#include "evaluation.h"
#include "list.h"
#include "game.h"
#include "ai.h"
#include <stdio.h>

/*
	Parameters:
	board : baghchal board
	mode : 
			1 -> tiger - human
			2 -> tiger - computer
			returns Winner Info.
		player 1 plays goats
*/
char game(Board * board, int mode){
	int turncounter = 0;
	List moves;

	//turncounter++; //debug -- comment to move goat first
	do{
		Move m;
		char turn;
		int tmp;

		turncounter++;
		turn = (turncounter%2==0)?TIGER:GOAT;

		if( is_game_over(board,turn,&moves) ){
			return turn==GOAT?TIGER:GOAT;
		}

		if(turn == GOAT)
			printf("Goat\n");
		else
			printf("Tiger\n");

#ifdef __PRINT_VALID_MOVES__
		print_list(moves);
		print_game(board);
#endif
		if(turn == TIGER && mode == 2){
			m = minimax(board,turn,-100,100,0);
			print_move(m);
			getchar(); //debug--wait before make move
		}else{

			//repeat until valid move
			do{
				m = user_move(board,turn);
			}while(! find_pos_in_list(&moves,m,&tmp));
		}
		execute_move(board,m);
		cleanup_list(&moves);
		print_game(board);
		printf("\n\n");

	}while(True);
}
