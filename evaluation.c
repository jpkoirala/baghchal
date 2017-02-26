#include "def.h"
#include "list.h"
#include "evaluation.h"
#include "io.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

const Point neighbours[NEIGHBOUR_COUNT] = {{1,-1},{1,0},{1,1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1}};

/*get moves for fixed point*/
List get_moves(const Board * board, char turn, Point from){
	List t;
	Move m;
	Point p1,p2;
	int i;

	initialize_list(&t);
	if(turn == GOAT){
		if(get_goat_in_hand_count(board) && is_empty(board,from)){
			p1 = new_point(-2,-2);

			m = new_move( p1, from , False );
			m.score = VMOVE;
			insert_at_last( &t, m );					
		} else {
			if( !board->goats_in_hand && who(board,from) == turn){
				p1 = from;
				for(i=0; i<NEIGHBOUR_COUNT; i++){
					p2 = addition(p1,neighbours[i]);
					if(is_inside(p2) && is_empty(board,p2) && are_adj_points(p1,p2)){
						m = new_move( p1, p2 , False);
						m.score = VMOVE;
						insert_at_last( &t, m );
					}
				}
			}
		}

	} else {
		if( who(board,from) == turn){
			p1 = from;
			for(i=0; i<NEIGHBOUR_COUNT; i++){
				p2 = addition(p1,neighbours[i]);
						
				if(is_inside(p2) && is_empty(board,p2) && are_adj_points(p1,p2)){
					m = new_move( p1, p2, False );
					m.score = VMOVE;
					insert_at_last( &t, m );
				}
				/*double the neighbour distance and add*/
				p2 = addition(p1,scalar_mul(neighbours[i],2));

				if( is_inside( p2 ) && is_jump_possible(board, p1, p2 ) ){
					m = new_move( p1, p2, True);//is eatable
					m.score = EAT_MOVE;
					m.attack_info = True;
					insert_at_first( &t, m);
				}
			}
		}
	}
	return t;
}



//score the move
void score(Board board, Move * m){
	int i;
	Point p1, p2;
	//const Point neighbours[NEIGHBOUR_COUNT] = {{1,-1},{1,0},{1,1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1}};

	execute_move(&board,*m);
	update_tiger_pos(&board);
	if(check_trap(&board)){
		m->score = MAKE_TRAP;
	}

	p1 = m->to;

	for(i=0; i<NEIGHBOUR_COUNT; i++){
		p2 = addition(p1,scalar_mul(neighbours[i],2));

		if( is_inside( p2 ) && is_jump_possible(&board, p1, p2 ) ){
			m->score = FOLLOW;
		}

	}
	undo_move(&board,*m);
}


List generate_moves(const Board * board, char turn){
	int i,j;
	List t;
	initialize_list(&t);

	/*Do not generate list bocoz Goats lost already*/
	if(get_dead_goat_count(board) == DEAD_GOAT_MAX){
		return t;
	}

	for(j=0;j<COL;j++){
		for(i=0;i<ROW;i++){
			List second = get_moves(board,turn,new_point(i,j));
			concatenate_list(&t,&second);
		}
	}
	
	for_each(*board,t,score);
	sort_by_score(&t,turn);

	return t;
}


boolean is_game_over(const Board * board, char turn, List * moves){
	// 5 is not enough for expert players
	if(turn==GOAT && get_dead_goat_count(board) == DEAD_GOAT_MAX){
		return True;
	}
	*moves = generate_moves( board, turn );
	return is_list_empty(*moves);
}



int check_trap(Board * board){

	int count=0,i,j;
	
	//debug
	/*
	for(i=0;i<4;i++){
		print_point(board->tiger_pos[i]);
	}
	printf("\n");
	*/
	for(i=0;i<TIGER_COUNT;i++){

		for(j=i+1;j<TIGER_COUNT;j++){

			//printf("%d %d\n",i,j); //debug
			/*distance 3 means two third step from the first eg. (0,0) to (0,3)*/
			if( distance_between(board->tiger_pos[i],board->tiger_pos[j])==3 &&
				is_empty_between(board,board->tiger_pos[i],board->tiger_pos[j],3) ){
				//remember the engaged
				//engage(board,board->tiger_pos[i]);
				//engage(board,board->tiger_pos[j]);
				count++;
			}
		}
	}
	return count;
}


int static_score(Board * board){
	int score = 0,i,j;
	Point dest;
	//const Point neighbours[NEIGHBOUR_COUNT] = {{1,-1},{1,0},{1,1},{0,-1},{0,1},{-1,-1},{-1,0},{-1,1}};
	update_tiger_pos(board);
	update_rooms(board,neighbours);
	if( board->goats_eaten > board->prev_goat_count ){
		return 90;
	}

	//checks if eat move exists
	for(i=0;i<TIGER_COUNT;i++){
		for(j=0;j<NEIGHBOUR_COUNT;j++){
			dest = addition(board->tiger_pos[i],scalar_mul(neighbours[j],2));
			if(is_jump_possible(board,board->tiger_pos[i],dest)){
				score = 10;
			}
		}
	}

	score += 5* check_trap(board); //strong point for tiger

	score += -10 * board->rooms_count; //strong point for goats team

	//debug
	//if(board->rooms_count){
	//	print_game(board);
	//	for(i=0;i<board->rooms_count;i++){
	//		print_point(board->rooms[i]);
	//		printf("\n");
	//	}
	//}

	return score;
}
