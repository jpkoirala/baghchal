#include "debug_def.h"
#include "def.h"		
#include "board.h"
#include "io.h"
#include "game.h"
#include "evaluation.h"
#include <stdio.h>



int main(int argc, char * argv[]){
#ifdef __MAIN__

	
	Board * board = initialize_board();


	print_game(board);

	if(game(board,2)==GOAT){
		printf("Game Over!\nGoats Won");
	}else{
		printf("Game Over!\nTigers Won");
	}

	destroy_board(board);

#endif

/*
	tests to check if some functionalities were correct
	or used to debug -- mostly move generation
*/


#ifdef TEST1
	int i,j,k,l;
	Point p1,p2;
	Move m;
	List t;
	Board * board;
	const Point neighbours[8] = {
		{-1,-1},{-1, 0},{-1, 1},
		{ 0,-1},        { 0, 1},
		{ 1,-1},{ 1, 0},{ 1, 1}
	};
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			board = initialize_board();
			initialize_list(&t);
			p1 = new_point(i,j);
			put(board,p1);
			for(k=0; k<8; k++){
				p2 = addition(p1,neighbours[k]);
				if(is_inside(p2) && is_empty(board,p2) && are_adj_points(p1,p2)){
					m = new_move( p1, p2, False );
					m.score = VMOVE;
					insert_at_last( &t, m );
				}
			}
			clear(board,p1);
			print_list(t);
			cleanup_list(&t);
			printf("\n");
			getchar();
		}
	}

#endif

#ifdef TEST2
	int i,j,k,l;
	Point p1,p2;
	Move m;
	List t,second,tmp;
	Board * board;
	const Point neighbours[8] = {
		{-1,-1},{-1, 0},{-1, 1},
		{ 0,-1},        { 0, 1},
		{ 1,-1},{ 1, 0},{ 1, 1}
	};

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			board = initialize_board();
			initialize_list(&t);
			p1 = new_point(i,j);
			put_ps(board,p1,TIGER);
			for(k=0; k<8; k++){
				p2 = addition(p1,neighbours[k]);
				if(is_inside(p2) && is_empty(board,p2) && are_adj_points(p1,p2)){
					m = new_move( p1, p2 , False);
					m.score = VMOVE;
					insert_at_last( &t, m );
				}
			}

			printf("___________________\n");
			print_list(t);
			tmp = t;
			for( ; tmp!=NULL; tmp = tmp->next){
				initialize_list(&second);
				put_ps(board,p1,TIGER);
				put_ps(board,tmp->move.to,GOAT);
				getchar();
				for(l=0;l<8;l++){
					p2 = addition(p1,two_times(neighbours[l]));
					
					if( is_inside( p2 ) && is_jump_possible(board, p1, p2 ) ){
						m = new_move( p1, p2, False);
						printf("TestMove->");
						print_move(m);
						printf("\n");
						print_game(board);
						m.score = EAT_MOVE;
						insert_at_first( &second, m);
					}

				}
				clear(board,tmp->move.to);
				printf("/*********eats************/\n");
				print_list(second);
				printf("/*******end eats**********/\n");
				cleanup_list(&second);
				getchar();//debug
			}


			clear(board,p1);
			print_game(board);
			cleanup_list(&t);
			printf("\n");
		}
	}

#endif
	getchar();
	return 0;
}