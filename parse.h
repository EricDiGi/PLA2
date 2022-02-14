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


void assignment();
void expression();
void term();
void factor();
void match();



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


void term(){
	factor();
	while(lookahead == ADD_OP || lookahead == SUB_OP || lookahead == MULT_OP || lookahead == DIV_OP){
		match(lookahead);
		factor();
	}
}

void factor(){
	if(lookahead == IDENT){
		match(IDENT);
	}
	else if(lookahead == INT_LIT){
		match(INT_LIT);
	}
	else if(lookahead == LEFT_PAREN){
		match(LEFT_PAREN);
		//expression();
		term();
		match(RIGHT_PAREN);
	}
	else{
		error("Mismatched Parenthesis");
		exit(0);
	}
}

void match(int token){
	if(lookahead == token){
		lookahead = lexan();
	}
	else{
		printf("Syntax error - Line %d - expected \'%s\' got %s\n",lineno,tableLookup(token),lexeme);
		exit(0);
	}
}

#endif
