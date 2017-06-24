rm test_O3.csv
touch test_O3.csv
for N in 256 512 1024 2048 4096 8192 16384	32768
do
  echo "Testing N = "$N
  ./lab2 $N >> test_O3.csv
done
