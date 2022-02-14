#!/bin/bash

if !(test -f "compile");
	then make;
fi
if !(test -f "compile");
	then printf "Must have been an error while compiling, Sorry!\n"
		exit;
fi

printf "\n"

for i in {1..8};
do 
	printf ">>> ./compile a$i\n"
	./compile "a$i"
	printf "\n";
done;
exit;
