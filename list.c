#include "list.h"
#include "def.h"
#include "io.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_list (List *list) {
	list->first = NULL;
	list->last = NULL;
	list->count = 0;
}

static Tpointer new_node(Move m){
	Tpointer newnode = (Tpointer)malloc(sizeof(Tnode));
	if(newnode==NULL){
		printf("memory not allocated: List::new_node()\n");
	}
	newnode->move = m;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}

void cleanup_list(List *list) {
    Tpointer tmp,prv;
    tmp = list->first;
    while (tmp != NULL) {
		prv = tmp->next;
		free(tmp);
		tmp = prv;
    }
    initialize_list(list);
}

void insert_at_first(List *list, Move m){
	Tpointer newnode = new_node(m);
	list->count++;
	if(list->last != NULL)
		list->first->prev = newnode;
	else
		list->last = newnode;
	newnode->next = list->first;
	list->first = newnode;
}

void insert_at_last(List *list, Move m) {
	Tpointer newnode = new_node(m);
	list->count++;
	if(list->last != NULL)
		list->first->prev = newnode;
	else
		list->last = newnode;
	newnode->next = list->first;
	list->first = newnode;
}

/*just for debugging*/
void print_list (List list) {
    Tpointer what;

    what = list.first;

    while (what != NULL) {
		print_move(what->move);
		printf("\n");
		what = what->next;
    }
}

int find_pos_in_list(const List *list, Move m, int *pos){
	int index=0;		//array like index
	Tpointer t = list->first;
	while(t != NULL){
		if( is_same_move(t->move , m )){
			*pos = index;
			return 1;
		}
		t = t->next;
		index++;
	}
	return 0;
}

boolean is_list_empty(const List list){
#ifdef _DEBUG
	if((list.first == NULL && list.last != NULL) || (list.first == NULL && list.last != NULL)){
		printf("Error in List -- called from is_list_empty");
		exit(-1);
	}
#endif
	return list.first == NULL ? True : False;
}

void concatenate_list(List * list1, List * list2){
	if(is_list_empty(*list2)) 
		return;
	if(is_list_empty(*list1)){
		*list1 = *list2;
		return;
	}
	list1->last->next = list2->first;
	list2->first->prev = list1->last;
	list1->last = list2->last;
	list1->count+=list2->count;
}

void move_to_first(List * list, Tpointer p){
	
	/***First Element***/
	if(p->prev == NULL){
		return;
	}

	if(p->next){
		/***In between***/
		p->next->prev = p->prev;
	}else{
		list->last = p->prev;//last element
	}

	p->prev->next = p->next; //isolated.

	p->next = list->first;
	p->prev = list->first->prev; //basically NULL
	list->first->prev = p;
	list->first = p;
}

void move_to_last(List * list, Tpointer p){
	
	/***Last Element***/
	if(p->next == NULL){
		return;
	}

	if(p->prev){
		/***In between***/
		p->prev->next = p->next;
	}else{
		list->first = p->next;//first element
	}

	p->next->prev = p->prev; //isolated.

	p->prev = list->last;
	p->next = list->last->next; //basically NULL
	list->last->next = p;
	list->last = p;
}

static void sort_by_score_tiger(List * list){
	//bigger values at first
	Tpointer tmp2,tmp ;

	if(is_list_empty(*list)){
		return;
	}

	tmp = list->first->next;
	while(tmp!=NULL){
		if(tmp->move.score >= list->first->move.score){
			tmp2 = tmp->next;
			move_to_first(list,tmp);
			tmp = tmp2;
		}else{
			tmp = tmp->next;
		}
	}

}

static void sort_by_score_goat(List * list){
	//smaller values at first
	Tpointer tmp2,tmp;
	if(is_list_empty(*list)){
		return;
	}
	tmp = list->first->next;
	while(tmp!=NULL){
		if(tmp->move.score <= list->first->move.score){
			tmp2 = tmp->next;
			move_to_first(list,tmp);
			tmp = tmp2;
		}else{
			tmp = tmp->next;
		}
	}

}

/*
	Todo:
	Use this for printing moves as well.
*/

void for_each(Board board,List list, void f(Board board, Move * ) ){
	Tpointer tmp;
    tmp = list.first;
    while (tmp != NULL) {
		f(board, &tmp->move);
		tmp = tmp->next;
    }
}

void sort_by_score(List * list, char turn){
	if(turn==TIGER){
		sort_by_score_tiger(list);
	}else{
		sort_by_score_goat(list);
	}
}