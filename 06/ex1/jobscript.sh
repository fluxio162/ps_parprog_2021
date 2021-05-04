#!/bin/bash

# Executes job in the queue "lva.q" unless you have special requirements.
#$ -q lva.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N sheet01Testing

# Redirect output stream to this file.
#$ -o output.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc

# ./path/to/application <command> <line> <arguments>
cd ~
cd S6
make 

./ex1_seq 1000000000

export OMP_NUM_THREADS=1
./ex1_par 1000000000

export OMP_NUM_THREADS=8
./ex1_par 1000000000

make clean