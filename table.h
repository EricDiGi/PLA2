#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "common.h"

/*****************************
 My table has O(1) lookup
******************************/

int categories = 6;

//Old table
/*char tab[6][10][20] = {
	{"<LETTER>","<DIGIT>","<UNKNOWN>"},
	{"<INT_LIT>","<IDENT>"},
	{"<COMMENT>","<WHITESPACE>","<NEWLINE>"},
	{"<UNDERSCORE>","<SEMICOLON>"},
	{"<ASSIGN_OP>","<ADD_OP>","<SUB_OP>","<MULT_OP>","<DIV_OP>","<LEFT_PAREN>","<RIGHT_PAREN>"},
	{"<BEGIN_PROG>","<END_PROG>"}
};*/
//This one helps build output better
char tab[6][10][20] = {
	{"<LETTER>","<DIGIT>","<UNKNOWN>"},
	{"Number Literal","Identifier"},
	{"Comment","<WHITESPACE>","<NEWLINE>"},
	{"_",";"},
	{"=","+","-","*","/","(",")"},
	{"BEGIN","END"}
};

int lens[6] = {3,2,3,2,7,2};

int depth = 0;

void printNode(struct node* n);
bool find(char* ident, struct node* N);

//Put symbol at head of list
void pushSymbol(int op, char* ident){
		if(find(ident, head)){return;}
		struct node* chain_link = (struct node*) malloc(sizeof(struct node));
		chain_link->op_code = op;
		strcpy(chain_link->lexeme, ident);
		strcpy(chain_link->pos, tab[((op - (op%10))/10)-1][op%10]);
	
		chain_link->next = head;
		head = chain_link;
}

char* tableLookup(int tok){
	return tab[((tok - (tok%10))/10)-1][tok%10];
}

// O(N) print time
void printTable(){

	struct node* temp = head;
	while(temp->next != NULL){
		printf("%s, ", temp->lexeme);
		temp = temp->next;
	}
	printf("%s\n", temp->lexeme);
}

//Auxilary functions

void printSymbol(int op, char* actual){
	int index_x = op%10;
	int index_y = ((op - (op%10))/10)-1;
	int limit = lens[index_y];
	if(index_x >= 0 && index_x < limit){
		printf("%s\t%s\t%d\n", tab[index_y][index_x], actual, op);
	}
}

void printNode(struct node* n){
	printf("%d\t\t\t%s\t\t%d\t\t\t%s\n", n->loc, n->lexeme,n->op_code, n->pos);
}

bool find(char *ident, struct node* N){
	if(N == NULL)
		return false;
	if(strcmp(N->lexeme,ident) == 0)
		return true;
	return find(ident, N->next);
}
#endif

