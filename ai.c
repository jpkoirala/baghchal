#include "io.h"
#include "def.h"
#include "board.h"
#include "evaluation.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

Move minimax(Board * board, char turn, int alpha, int beta, int level){
	Move best;
	Move reply;
	char opp_turn;

	//char * state = NULL; //string of board position (to save)

	List moves;
	Tpointer tmp; //temporary variable to go through all the moves in list
	int stat_score; //score for the board--static score

	level++;
	initialize_list(&moves);

//#define __PRINT_ANALYSIS__
	
	if( is_game_over(board,turn,&moves)){
		
		if(turn == TIGER){
			//Goat's winning position
			best.score = -100;
		} else if( turn == GOAT){
			//Tiger's Winning Position
			best.score = 100;
		}
		level--;
		cleanup_list(&moves);
		return best;
	} else {
		
		/*

		if( turn == GOAT ){
			//if it is not game over and it is tiger's eat move then go for it //heuristic for tiger
			if(board->goats_eaten > board->prev_goat_count){
				best.score_depth = level;
				best.score = 5;
				level--;
				cleanup_list(&moves);
				return best;
			}
		}
		*/
		

		if ( level == MAXLEVEL){ //force to after certain depth

			if(turn == TIGER){
				best.score = 99;
			} else if( turn == GOAT){
				best.score = -99;
			}


			level--;

			cleanup_list(&moves);
			return best;
		}
	}
	/*******DEBUG START*****************/
	/*if(level>=3){
		printf("BASMATI CHAMAL MA DHUNGO\n");
	}*/

	
	/*******DEBUG END*****************/
	if(turn == TIGER){
		best.score = alpha;
	}else{
		best.score = beta;
	}
	
	
	tmp = moves.first;

	//printf("*********%c**********\n",turn);
	//print_list(moves);
	while(tmp != NULL){
		execute_move(board,tmp->move);

		#ifdef __PRINT_ANALYSIS__
		printf("EXECUTE\n");
		print_game(board);
		#endif
		/***********BOARD ANALYSIS-OPTIMIZATION NEEDED****************/
		//FIXME
		//analysis (dropped for now)

		//state = copy(board,turn);
		//if(analyzed(board,state)){
		//	undo_move(board,tmp->move);
		//
		//#ifdef __PRINT_ANALYSIS__
		//	printf("UNDO - analyzed\n");
		//	print_game(board);
		//#endif
		//
		//	free(state);
		//	tmp=tmp->next;
		//	breadth++;
		//	continue;
		//}else{
		//	store_state(board,state);
		//}

		/***********BOARD ANALYSIS END****************/
		
		/*******DEBUG START*****************/

		//printf("Level %d\n",level);
		

		/*******DEBUG END*****************/

		opp_turn = turn==TIGER?GOAT:TIGER;
		stat_score = static_score(board);
		reply = minimax(board,opp_turn,alpha,beta,level);
		undo_move(board,tmp->move);


		#ifdef __PRINT_ANALYSIS__
		printf("UNDO\n");
		print_game(board);
		#endif

		if((turn == TIGER) && (reply.score > best.score || stat_score > best.score) ) {
			best = tmp->move;
			if(reply.score > stat_score){
				best.score = reply.score;
			}else{
				best.score = stat_score;
			}
			alpha = best.score;
			best.score_depth = reply.score_depth;
		}
		if((turn == GOAT ) && (reply.score < best.score || stat_score < best.score)) {
			best = tmp->move;
			if(reply.score < stat_score){
				best.score = reply.score;
			}else{
				best.score = stat_score;
			}
			beta = best.score;
			best.score_depth=reply.score_depth;
		}

		tmp = tmp->next;

	}
	///////////////////////////////////////////////////////////////
	//take the move from less-depth
	/*if( (turn == TIGER) && (score > best.score)) {
		best = tmp->move;
		best.score = reply.score;
		alpha = reply.score;
		best.score_depth = reply.score_depth;
	}
	else if((turn == GOAT ) && (reply.score < best.score)) {
			best = tmp->move;
			best.score = reply.score;
			beta = reply.score;
	}*/


	/*******DEBUG START*****************/
	level--;
	/*******DEBUG END*****************/

	cleanup_list(&moves);
	return best;
}