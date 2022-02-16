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
		if(lookahead == IDENT || lookahead == INT_LIT){
			
		}
		lookahead = lexan();
	}
	else{
		printf("Syntax error - Line %d - expected \'%s\' got %s\n",lineno,tableLookup(token),lexeme);
		exit(0);
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
		putSymbol(lookahead, lexeme);
		match(IDENT);
	}
}

// A -> i = T;
void assignment(){
	char a[30];
	strcpy(a,lexeme);

	registers = 0;
	
	match(IDENT);
	if(lookahead != ASSIGN_OP){
		error("Missing Assignment Operator \'=\'");
		exit(0);
	}

	match(ASSIGN_OP);
	term();
	match(SEMICOLON);
	//printf("R%d = R%d\n", registers-1, registers);
	registers -= 1;
	printf("%s = R%d\n", a,registers);
}

// T -> BF(OF)*b | BTb
void term(){
	int op;
	//char* reg = assocRegister(lexeme);
	factor();

	while(lookahead == ADD_OP || lookahead == SUB_OP || lookahead == MULT_OP || lookahead == DIV_OP){
		int op = lookahead;
		match(lookahead);
		factor();
		
		printf("R%d = R%d %s R%d\n", registers-2,registers-2, tableLookup(op),registers);
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
			exit(0);
		}
		printf("R%d = %s\n", registers++, lexeme);
		match(IDENT);
	}
	else if(lookahead == INT_LIT){
		printf("R%d = %s\n", registers++, lexeme);
		match(INT_LIT);
	}
}

#endif
