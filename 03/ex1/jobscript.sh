echo "module load gcc/8.2.0"
module load gcc/8.2.0

echo "make clean"
make clean
echo "make"
make

echo "critical"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex1_critical; done
echo "atomic"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex1_atomic; done
echo "reduction"
for i in 1 2 4 8; do OMP_NUM_THREADS=$i ./ex1_reduction; done

echo "make clean"
make clean

echo "module unload gcc/8.2.0"
module unload gcc/8.2.0