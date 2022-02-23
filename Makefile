CXX = gcc
CXXFLAGS = -g -Wall

SRCS = $(wildcard *.h)
OBJECTS = $(SRCS: .h=.o)

all: compile

compile: $(OBJECTS) main.c common.h parse.h table.h lexeme.h
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* test/*.o core compile *.out
