CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp

.PHONY: all
all: ex1_seq ex1_par

.PHONY: clean
clean:
	$(RM) ex1_seq ex1_par

ex1_seq: ex1_seq.c
ex1_par: ex1_par.c

