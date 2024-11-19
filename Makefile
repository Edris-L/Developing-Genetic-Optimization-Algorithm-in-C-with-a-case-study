# Variables for compiler and flags
CC = gcc
CFLAGS = -Wall -O2
LM = -lm

# Targets and their dependencies
all: GA

# Building the final executable
GA: functions.o OF.o GA.o
	$(CC) $(CFLAGS) -o GA functions.o OF.o GA.o $(LM)

# Compile functions.c
functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

# Compile OF.c
OF.o: OF.c
	$(CC) $(CFLAGS) -c OF.c -o OF.o

# Compile GA.c
GA.o: GA.c
	$(CC) $(CFLAGS) -c GA.c -o GA.o

# Clean rule to remove object files and executable
clean:
	rm -f *.o GA