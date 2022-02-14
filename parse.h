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
void t_match(int, int);

void match(int token){
	if(lookahead == token){
		lookahead = lexan();
	}
	else{
		printf("Syntax error - Line %d - expected \'%s\' got %s\n",lineno,tableLookup(token),lexeme);
		exit(0);
	}
}

void t_match(int token, int type){
	if(lookahead == token){
		if(lookahead != SEMICOLON)
			putSymbol(type, lexeme);
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
		putSymbol(type, lexeme);
		putRegister(lexeme, head, registers);
		match(IDENT);
	}
}

// A -> i = T;
void assignment(){
	match(IDENT);
	if(lookahead != ASSIGN_OP){
		error("Missing Assignment Operator \'=\'");
		exit(0);
	}
	match(ASSIGN_OP);
	term();
	match(SEMICOLON);
}

// T -> BF(OF)*b | BTb
void term(){
	factor();
	while(lookahead == ADD_OP || lookahead == SUB_OP || lookahead == MULT_OP || lookahead == DIV_OP){
		match(lookahead);
		factor();
	}
}

// 
void factor(){
	if(lookahead == IDENT){
		if(!find(lexeme,head)){
			printf("Error - line %d - Variable %s not declared\n", lineno, lexeme);
			exit(0);
		}
		putSymbol(lookahead, lexeme);
		putRegister(lexeme, head, registers);
		match(IDENT);
	}
	else if(lookahead == INT_LIT){
		putSymbol(lookahead, lexeme);
		putRegister(lexeme, head, registers);
		match(INT_LIT);
	}
	else if(lookahead == LEFT_PAREN){
		match(LEFT_PAREN);
		if(lookahead == RIGHT_PAREN){
			printf("Error - line %d - Expected identifier or literal got ')'\n", lineno);
			exit(EXIT_FAILURE);
		}
		term();
		match(RIGHT_PAREN);
	}
}

#endif
