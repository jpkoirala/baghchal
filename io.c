#include <stdio.h>
#include "def.h"
#include "board.h"

void print_game(const Board * ps){
	int o_loop,l_count=10,l_start=0,plus=1,i,n=0,f=10,inc=-1,a_inc=11,c=-1;
	char front_s=47,back_s=92;
	char front_b=47,back_b=92;
    int x,y;
	printf("\n\n");
	printf("    a        b        c        d        e\n");
	printf("                                         \n");

	do{
		n++;
		for(o_loop=l_start;o_loop<=l_count;o_loop++){
			if(o_loop%5==0){
				printf(" %d  ",1 + o_loop/COL);
				a_inc--;
				if(plus)
					inc++;
				else
					inc--;

				for(i=0;i<=20;i++){
					if(i%5==0){
						c++;
						x=c%ROW;
						y=c/COL;
						printf("%c", (ps->pieces[x][y].piece));
					}else{
						printf("--");
					}
				}
				printf("  %d ",1 + o_loop/COL);
			}else{
				printf("    ");
				a_inc--;
				if(plus)
					inc++;
				else
					inc--;
				for(i=0;i<=20;i++){
					if(i%5==0)
						printf("|");
					else if((f+inc)==i)
						printf("%c ",back_s);
					else  if((f-inc)==i)
						printf(" %c",front_s);
					else if((f-a_inc)==i)
						printf("%c ",back_b);
					else if((f+a_inc)==i)
						printf(" %c",front_b);
					else
						printf("  ");
				}
			}
				printf("\n");
		}

		inc=10;
		l_count=20;
		l_start = 11;
		plus=0;
		front_s=92;
		back_s=47;

	}while(n<2);

	printf("                                        \n");
	printf("    a        b        c        d        e\n");
	printf("GOATS in HANAD : %d\n",ps->goats_in_hand);
	printf("GOATS EATEN : %d\n\n",ps->goats_eaten);
}

Point input(char * prompt)
{
    Point p;
    int char_value=0;
    char buffer[10];
	char x,y,z;
	/*
		clear the buffer from input stream;
		read more characters in temporary buffer from input
		and take required values
	*/
	printf("%s\n",prompt);
	fflush(stdin);
	fflush(stdout);
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%c%c%c" ,&x,&y,&z);

	p.x = x - 'a';
	p.y = y - '1';

	if(y < '1' || y > '5')
		p.y = z - '1';

    while (p.x<0 || p.x>4 || p.y<0 || p.y>4) //parse the inputs
    {
		fflush(stdin);
        printf("Invalid Point!\n Use this format [a-e][1-5] \n");
		printf("\n        %s:",prompt);
		//read the inputs (location) in a buffer
		//then in the Point variable

        fflush(stdin);
		fflush(stdout);
		fgets(buffer, 80, stdin);
		sscanf(buffer, "%c" ,&y);
		sscanf(buffer, "%c%c%c" ,&x,&y,&z);

		p.x = x - 'a';
		p.y = y - '1';

		if(y==' ')
			p.y = z - '1';
    }
    return p; //return it.
}

/*
	test: if the goat is first 20
	turn: tiger or goat
*/
Move user_move(const Board * b, char turn){
	Point from,to;

	if(turn == GOAT && b->goats_in_hand)
		from = new_point(-2,-2);
	else{
		from = input("From: ");
		while(turn != who(b,from)){
			from = input("Wrong Input! Try Again!\nFrom: ");
		}
	}

	to = input("To: ");
	while(!is_empty(b,to)){
		to = input("Wrong Input! Try Again!\nTo: ");
	}


	/*recursion. wow!*/
	if(is_same_point(from,to))
		return user_move(b,turn);

	return new_move(from,to,False);
}

void print_point(const Point p){
	printf("(%c,%c)",'a'+p.x,'1'+p.y);
}

void print_move(const Move m){
	printf("From : ");
	print_point(m.from);
	printf(" TO : ");
	print_point(m.to);
}
