module load gcc/10.3.0
make

./ex1 10 1000000
./ex1 100 1000000
./ex1 1000 1000000
./ex1 2048 1000000


./ex1 10 10000000
./ex1 100 10000000
./ex1 1000 10000000
./ex1 2048 10000000


make clean
module unload gcc/10.3.0