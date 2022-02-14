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

		while(lookahead != BEGIN_PROG){
			match(lookahead);
			if(lookahead == DONE){
				perror("Never found start of program\n");
				exit(EXIT_FAILURE);
			}
		}
		match(BEGIN_PROG);
		while(lookahead != END_PROG){
			if(lookahead == DONE){
				perror("Never found start of program\n");
				exit(EXIT_FAILURE);
			}
			process();
		}
		printf("Success!\n");
		//printTable();
	}
}

