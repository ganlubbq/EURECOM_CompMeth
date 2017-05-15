make clean
make CFLAGS=-O0

rm sse_O0.csv
touch sse_O0.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768
do
  echo "Testing N = "$N
  ./lab2 $N >> sse_O0.csv
done

make clean
make CFLAGS=-O1

rm sse_O1.csv
touch sse_O1.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768
do
  echo "Testing N = "$N
  ./lab2 $N > sse_O1.csv
done

make clean
make CFLAGS=-O2

rm sse_O2.csv
touch sse_O2.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768
do
  echo "Testing N = "$N
  ./lab2 $N >> sse_O2.csv
done

make clean
make CFLAGS=-O3

rm sse_O3.csv
touch sse_O3.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768
do
  echo "Testing N = "$N
  ./lab2 $N > sse_O3.csv
done
