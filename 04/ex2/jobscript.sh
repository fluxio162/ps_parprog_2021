echo "module load gcc/8.2.0"
module load gcc/8.2.0

make clean
make 

for i in {1..1000}; do ./flush; done


echo "module unload gcc/8.2.0"
module unload gcc/8.2.0