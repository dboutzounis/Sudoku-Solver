# compile with gcc
CC=gcc

# Compiler options:
#
# -pg is used for profiling (gprof)
CFLAGS = -g -Wall -Werror

# Linker options:
#
# -lm: link with the math library
LDFLAGS += -lm

# set the name of the executable file to compile here
PROGRAM = sudoku
LAB = test

OBJS = ./src/main.o ./src/sudoku.o ./src/solver.o ./src/Dancing-Links/dancing-links.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS) 