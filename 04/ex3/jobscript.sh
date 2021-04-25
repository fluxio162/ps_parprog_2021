#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N nh_job

# Redirect output stream to this file.
#$ -o output.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

# Set up any environment variables

#$ -l h_vmem=4G
cd S4
cd ex3
make

echo "sequential mergesort"
for i in 1 8; do echo "Threads: $i" && export OMP_NUM_THREADS=$i && ./merge_seq; done
echo "parallel mergesort"
for i in 1 8; do echo "Threads: $i" && export OMP_NUM_THREADS=$i && ./merge_par; done


echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0

