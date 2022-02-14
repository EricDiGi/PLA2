#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/*******************************

FILE CONTAINS ELEMENT SHARED BY ALL MODULES

********************************/

// Program will arithmatically ignore DONE when approaching the symbol lookup
enum Token {
	DONE = -1,
	LETTER=10, DIGIT, STOP, UNKNOWN, 
	INT_LIT = 20, IDENT, 
	COMMENT = 30, WHITESPACE, NEWLINE, 
	UNDERSCORE = 40, SEMICOLON, 
	ASSIGN_OP = 50, ADD_OP, SUB_OP, MULT_OP, DIV_OP, LEFT_PAREN, RIGHT_PAREN,
	BEGIN_PROG = 60, END_PROG
};


struct node{
	int op_code;
	char lexeme[256];
	char pos[20];
	int loc;
	struct node* next;
};

char ch;
FILE* in_fp;

int lookahead;
char looker;
int currToken;

int lineno = 1;

struct node* head;

void error(char* message){
	printf("Error - Line %d - %s\n", lineno, message);
}

#endif
