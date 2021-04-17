CFLAGS = -std=gnu11 -Wall -Wextra -pthread -fopenmp -lm

.PHONY: all
all: ex1_critical ex1_atomic ex1_reduction

.PHONY: clean
clean:
	$(RM) ex1_critical ex1_atomic ex1_reduction

ex1_critical: ex1_critical.c
ex1_atomic: ex1_atomic.c
ex1_reduction: ex1_reduction.c
