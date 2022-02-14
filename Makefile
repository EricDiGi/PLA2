CXX = gcc
CXXFLAGS = -g -std=c++11 -Wall

SRCS = $(wildcard *.h)
OBJECTS = $(SRCS: .h=.o)

all: compile

compile: $(OBJECTS) main.c common.h parse.h table.h lexeme.h
	$(CXX) -o $@ $^

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* test/*.o core main compile
