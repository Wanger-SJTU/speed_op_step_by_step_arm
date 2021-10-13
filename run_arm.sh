
sed -i 's/clang++/\$\{NDK_CXX\}/g' Makefile

m=$1
k=$2
n=$3

make perf

adb push build/main /data/tmp/main

adb shell "cd /data/tmp && chmod +x matmul && ./main $m $k $n"

sed -i 's/${NDK_CXX}/clang++/g' Makefile
# make clean