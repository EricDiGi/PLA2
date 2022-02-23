#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "table.h"
#include "lexeme.h"

/*********************************
OPERATES AS REGULAR GRAMMAR
*********************************/
void process();
void declaration();
void variable(int);
void assignment();
void term();
void factor();
void match(int);

void match(int token){
	if(lookahead == token){
		lookahead = lexan();
	}
	else{
		printf("Syntax error - Line %d - expected \'%s\' got %s\n",lineno,tableLookup(token),lexeme);
		exit(EXIT_FAILURE);
	}
}

//Q -> [D*A*]* | e
void process(){
	while(lookahead == DTYPE){
		declaration();
	}
	while(lookahead == IDENT){
		assignment();
	}
}

// D -> tV;
void declaration(){
	int type = UNKNOWN;
	if(lookahead == DTYPE){
		type = type_lookup(lexeme);
	}
	match(DTYPE);
	variable(type);
	match(SEMICOLON);
}

// V -> i*
void variable(int type){
	while(lookahead == IDENT){
		putSymbol(type, lexeme);
		match(IDENT);
	}
}

// A -> i = T;
void assignment(){
	char a[30];
	strcpy(a,lexeme);

	if(lookahead == DTYPE){
		match(DTYPE);
		if(find(lexeme, head)){
			printf("Error - line %d - Redeclaration of %s\n", lineno, lexeme);
			exit(EXIT_FAILURE);
		}
	}
	if(lookahead == IDENT && !find(lexeme,head)){
		printf("Error - line %d - Variable %s is undefined\n", lineno, lexeme);
		exit(EXIT_FAILURE);
	}


	match(IDENT);
	if(lookahead != ASSIGN_OP){
		error("Missing Assignment Operator \'=\'");
		exit(EXIT_FAILURE);
	}

	match(ASSIGN_OP);
	term();
	match(SEMICOLON);

	registers -= 1;
	sprintf(output_buffer+strlen(output_buffer),"%s = R%d\n", a,registers);
	printSmall();
	freeSmall();
}

// T -> BF(OF)*b | BTb
void term(){

	factor();

	while(lookahead == ADD_OP || lookahead == SUB_OP || lookahead == MULT_OP || lookahead == DIV_OP){
		putSmall(lookahead, tableLookup(lookahead));

		int op = lookahead;
		match(lookahead);
		factor();
		sprintf(output_buffer+strlen(output_buffer),"R%d = R%d %s R%d\n", registers-2,registers-2, tableLookup(op),registers-1);
		registers -= 1;

	}
}

void factor(){

	if(lookahead == LEFT_PAREN){
		match(LEFT_PAREN);
		if(lookahead == RIGHT_PAREN){
			printf("Error - line %d - Expected identifier or literal got ')'\n", lineno);
			exit(EXIT_FAILURE);
		}
		term();
		match(RIGHT_PAREN);
	}
	else if(lookahead == IDENT){
		if(!find(lexeme,head)){
			printf("Error - line %d - Variable %s not declared\n", lineno, lexeme);
			exit(EXIT_FAILURE);
		}
		sprintf(output_buffer+strlen(output_buffer),"R%d = %s\n", registers++, lexeme);
		match(IDENT);
	}
	else if(lookahead == INT_LIT){
		sprintf(output_buffer+strlen(output_buffer),"R%d = %s\n", registers++, lexeme);
		match(INT_LIT);
	}

	putSmall(lookahead, lexeme);
}

#endif
