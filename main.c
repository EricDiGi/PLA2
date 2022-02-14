#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "lexeme.h"
#include "table.h"
#include "parse.h"

/*************************************

PROGRAM CLOSELY APPROXIMATES
	PSEUDOCODE PROVIDED IN CLASS
	& THE CODE PROVIDED IN: 
		Concepts of Programming Languages by Robert W. Sebesta


**************************************/


//Note to self, main is a part of the parsing scheme, not the lexan
int main(int argc, char** argv){
	if((in_fp = fopen(argv[1], "r")) == NULL){
		printf("Error cannot open %s", argv[1]);
	}
	else{
		printf("Compiling...\n");
		
		lookahead = lexan();
		match(BEGIN_PROG);
		while(lookahead != DONE){
			if(lookahead != BEGIN_PROG)
				assignment();
			if(lookahead == END_PROG){
				printf("Success\n");
				printTable();
				exit(0);
			}
		}
		error("Program has no End");
	}
}

