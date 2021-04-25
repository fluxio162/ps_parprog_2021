

# Set gcc version
CC=gcc-8

# Set compiler flags
CFLAGS = -std=gnu11 -Wall -Wextra -pthread -fopenmp -lm -O3

# Set rule for all
.PHONY: all
all: ex1 
# Set rule for clean
.PHONY: clean
clean:
	$(RM) ex1

ex1: ex1.c
