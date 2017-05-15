make clean
make CFLAGS="-O0 -mavx -mavx2"

rm avx_O0.csv
touch avx_O0.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768 65536 131072 262144 524288 1048576
do
  echo "Testing N = "$N
  ./lab2 $N >> avx_O0.csv
done

make clean
make CFLAGS="-O1 -mavx -mavx2"

rm avx_O1.csv
touch avx_O1.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768 65536 131072 262144 524288 1048576
do
  echo "Testing N = "$N
  ./lab2 $N >> avx_O1.csv
done

make clean
make CFLAGS="-O2 -mavx -mavx2"

rm avx_O2.csv
touch avx_O2.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768 65536 131072 262144 524288 1048576
do
  echo "Testing N = "$N
  ./lab2 $N >> avx_O2.csv
done

make clean
make CFLAGS="-O3 -mavx -mavx2"

rm avx_O3.csv
touch avx_O3.csv

for N in 16 32 64 128 256 512 1024 2048 4096 8192 16384	32768 65536 131072 262144 524288 1048576
do
  echo "Testing N = "$N
  ./lab2 $N >> avx_O3.csv
done
