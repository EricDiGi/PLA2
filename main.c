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
				printf("Never found start of program\n");
				exit(EXIT_FAILURE);
			}
		}
		putSymbol(lookahead, lexeme);
		match(BEGIN_PROG);
		while(lookahead != END_PROG){
			if(lookahead == DONE){
				printf("Never found start of program\n");
				exit(EXIT_FAILURE);
			}
			process();
		}
		putSymbol(lookahead, lexeme);
		freeHead();
		fclose(in_fp);



		char f_name[8] = {0};
		int i = 0;
		while(*(argv[1]) != '.' && *(argv[1]) != 0){f_name[i] = *(argv[1]); i++; argv[1]++;}
		sprintf(f_name+strlen(f_name), ".out");
		o_fp = fopen(f_name, "w");
		fwrite(output_buffer, sizeof(char), strlen(output_buffer), o_fp);
		fclose(o_fp);


		printf("%s\n",output_buffer);
		//printf("Success!\n");
		//printTable();
	}
}

