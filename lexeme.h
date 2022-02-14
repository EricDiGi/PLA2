#ifndef LEXEME_H
#define LEXEME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"
#include "table.h"

/*************************************

LEXICAL ANALYSIS
PERFORMED IN LINEAR FASHION

- Tokenize string

*************************************/

int lexLen;

int lexan();
bool isValid(char* c);
void putLexeme(char c);
int lookup(char c);
int reservation();


int lexan(){
	lexLen = 0;
	
	while(1){
		ch = getc(in_fp);
		if(ch == 32 || ch == 9 || ch == ','){}
		else if(ch == '\n'){lineno++;}
		else if(ch == '~'){
			while((ch = getc(in_fp)) != '\n'){}
			ungetc(ch,in_fp);
		}
		else if(isdigit(ch)){
			putLexeme(ch);
			while(isdigit(ch = getc(in_fp)))
				putLexeme(ch);
			ungetc(ch,in_fp);
			return INT_LIT;
		}
		else if(isalpha(ch)){
			putLexeme(ch);
			while(isalpha(ch = getc(in_fp)) || isdigit(ch) || ch == '_' || ch == '.')
				putLexeme(ch);
			ungetc(ch,in_fp);
			int tok = reservation();
			return tok;
		}
		else if (ch == EOF){
			return DONE;
		}
		else{
			return lookup(ch);
		}

	}
}

void putLexeme(char c){
	if( lexLen <= 255){
		lexeme[lexLen++] = c;
		lexeme[lexLen] = 0;
	}
	else{
		error("Lexeme too long");
	}
}

int lookup(char c){
	int token;
	switch(c){
		case '~':
			token = COMMENT;
			break;
		case '=':
			token = ASSIGN_OP;
			break;
		case '(':
			token = LEFT_PAREN;
			break;
		case ')':
			token = RIGHT_PAREN;
			break;
		case '+':
			token = ADD_OP;
			break;
		case '-':
			token = SUB_OP;
			break;
		case '*':
			token = MULT_OP;
			break;
		case '/':
			token = DIV_OP;
			break;
		case ';':
			token = SEMICOLON;
			break;
		default:
			token = UNKNOWN;
			break;
	}
	return token;
}


// Check for reserved cases

int reservation(){
	if(strcmp(lexeme, "begin") == 0){
		return BEGIN_PROG;
	}
	else if(strcmp(lexeme, "end.") == 0){
		return END_PROG;
	}
	else if(strcmp(lexeme, "int") == 0){
		return DTYPE;
	}
	if(!isValid(lexeme)){
		printf("Error - Line %d - Invalid Identifier %s\n", lineno, lexeme);
		exit(0);
	}
	return IDENT;
}

int type_lookup(char* l){
	if(strcmp(l,"int") == 0){
		return INT;
	}
	return UNKNOWN;
}

// Check identifier doesn't have chained or dangling underscores
bool isValid(char* c){
	int under_count = 0;
	while(*c != 0){
		if(*c == '_'){under_count++;}
		if(under_count >= 2){
			return false;
		}
		c++;
	}
	c--;
	if(*c == '_'){
		return false;
	}
	return true;
}

#endif
