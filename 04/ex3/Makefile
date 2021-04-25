# Set compiler flags
CFLAGS = -std=gnu11 -Wall -Wextra -pthread -fopenmp -lm -O3

# Set rule for all
.PHONY: all
all: merge_seq merge_par
# Set rule for clean
.PHONY: clean
clean:
	$(RM) merge_seq merge_par

merge_seq: merge_seq.c
merge_par: merge_par.c