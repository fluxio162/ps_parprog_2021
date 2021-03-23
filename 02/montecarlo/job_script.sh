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

gcc -pthread ~/ParalleleProgrammierung/montecarlo/mc_seq.c -o mc_sq && /usr/bin/time -v ./mc_seq
gcc -pthread ~/ParalleleProgrammierung/montecarlo/mc_par.c -o mc_par && /usr/bin/time -v ./mc_par