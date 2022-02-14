#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "table.h"
#include "lexeme.h"

/*********************************
OPERATES AS A PUSHDOWN AUTOMATA
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
		pushSymbol(lookahead, lexeme);
	}
	else{
		printf("Syntax error - Line %d - expected \'%s\' got %s\n",lineno,tableLookup(token),lexeme);
		exit(0);
	}
}

void t_match(int token, int type){
	if(lookahead == token){
		lookahead = lexan();
		pushSymbol(type, lexeme);
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
// V -> i*
void declaration(){
	int type = UNKNOWN;
	if(lookahead == DTYPE){
		type = type_lookup(lexeme);
	}
	t_match(DTYPE, type);
	variable(type);
	match(SEMICOLON);
}

void variable(int type){
	while(lookahead == IDENT){
		//printf("lexeme: %s :: %d\n", lexeme, type);
		t_match(IDENT, type);
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
		match(IDENT);
	}
	else if(lookahead == INT_LIT){
		match(INT_LIT);
	}
	else if(lookahead == LEFT_PAREN){
		match(LEFT_PAREN);
		term();
		match(RIGHT_PAREN);
	}
	else{
		error("Mismatched Parenthesis");
		exit(0);
	}
}

#endif
