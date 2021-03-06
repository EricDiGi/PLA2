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
	{"<LETTER>","<DIGIT>","<STOP>","<UNKNOWN>", "type identifier","Integer"},
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
bool putRegister(char* ident, struct node* N, int n);

int putSymbol(int op, char* ident){
	int idex = -1;
	struct node* chain_link = (struct node*)malloc(sizeof(struct node));
	chain_link->op_code = op;
	strcpy(chain_link->lexeme, ident);
	strcpy(chain_link->pos, tab[((op - (op%10))/10)-1][op%10]);

	if(head == NULL){
		head = chain_link;
		idex = 0;
		return idex;
	}
	else if(!find(ident, head)){
		//printf("%s\n",ident);
		idex = 0;
		struct node* temp = head;
		while(temp->next != NULL){
			temp = temp->next;
			idex++;
		}
		temp->next = chain_link;
		idex++;
		return idex;
	}
	return idex;
}

bool putRegister(char* ident, struct node* N, int n){
	if(N == NULL)
		return false;
	if(strcmp(N->lexeme,ident) == 0){
		sprintf(N->reg, "R%d", n);
		return true;
	}
	return putRegister(ident, N->next, n);
}

bool hasRegister(char* l){
	if(head == NULL){
		return 0;
	}
	else{
		struct node* temp = head;
		while(temp->next != NULL){
			if(strcmp(temp->lexeme, l) == 0){
				return true;
			}
			temp = temp->next;
		}
	}
	return false;
}

char* tableLookup(int tok){
	return tab[((tok - (tok%10))/10)-1][tok%10];
}

// O(N) print time
void printTable(){

	struct node* temp = head;
	while(temp->next != NULL){
		printNode(temp);
		temp = temp->next;
	}
	//printf("%s\n", temp->lexeme);
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
	printf("%s\t\t%d\t\t\t%s\t\t\t%s\n", n->lexeme,n->op_code,n->reg, n->pos);
}

bool find(char *ident, struct node* N){
	if(N == NULL){
		return false;
	}
	if(strcmp(N->lexeme, ident) == 0){
		return true;
	}
	return find(ident,N->next);
}

bool putSmall(int op, char* ident){
	bool idex = true;
	struct node* chain_link = (struct node*) malloc(sizeof(struct node));
	chain_link->op_code = op;
	strcpy(chain_link->lexeme, ident);
	strcpy(chain_link->pos, tab[((op - (op%10))/10)-1][op%10]);

	if(small == NULL){
		small = chain_link;
		idex = true;
		return idex;
	}
	else{ //if (op > 50 && op < 60){
		idex = true;
		struct node* temp = small;
		while(temp->next != NULL && chain_link){
			temp = temp->next;
		}
		temp->next = chain_link;
		return idex;
	}
	/*else if((op > 50 && op < 60) || !find(ident, small)){
		idex = true;
		struct node* temp = small;
		while(temp->next != NULL && chain_link){
			temp = temp->next;
		}
		temp->next = chain_link;
		return idex;
	}*/
	return idex;
}

void printSmall(){
	struct node* temp = small;
	sprintf(output_buffer+strlen(output_buffer), "*****[");
	while(temp->next != NULL){
		sprintf(output_buffer+strlen(output_buffer),"%s, ",temp->lexeme);
		temp = temp->next;
	}
	sprintf(output_buffer+strlen(output_buffer),"%s]*****\n", temp->lexeme);
}

void freeHead(){
	struct node* temp;

	while (head != NULL)
    {
       temp = head;
       head = head->next;
       free(temp);
    }
}

void freeSmall(){
	small = NULL;
}

#endif

