make clean
echo "Set Threads = 4, threads"
export OMP_NUM_THREADS=4
# defines which has 4 hardware thrreads
export OMP_DISPLAY_ENV=true
echo "OMP_PROC_PLACES=cores"
echo "OMP_PROC_BIND=close"
export OMP_PLACES=cores
export OMP_PROC_BIND=close
make
./ex1
make clean

