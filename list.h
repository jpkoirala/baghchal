#include "def.h"
#ifndef __LIST_H__
#define __LIST_H__

typedef struct node *Tpointer;

typedef struct node {
	Move move;
	Tpointer next;
	Tpointer prev;
} Tnode;

typedef struct {
	Tpointer first;
	Tpointer last;
	int count; //for debugging
} List;

/*
	initialize any new List variable
*/
void initialize_list (List *list);
/*
	insert new node at last
*/
void insert_at_last(List *list, Move m);
/*
	insert new node at the beginning of the list
*/
void insert_at_first(List *list, Move m);
/*
	print all moves in list
*/
void print_list (List list);
/*
	release memory allocated in for node in list
*/
void cleanup_list(List *list);
/*
	checks if any given move exists on the list
*/
int find_pos_in_list(const List *list, Move m, int *pos);

/*
	checks if the list is empty
*/
boolean is_list_empty(const List list);
/*
	concatenates two lists
*/
void concatenate_list(List * list1, List * list2); //concatenates to first list
/*
	simple sorting mechanism for list--these two functions are used by sort_by_score function
*/
void move_to_first(List * list, Tpointer p);
void move_to_last(List * list, Tpointer p);

/*
	a multipurpose function for Lists
*/

void for_each(Board board,List list, void f(Board board, Move * ) );

/*
	sorts the list of moves according to score given to the moves
*/

void sort_by_score(List * list,char turn);

#endif