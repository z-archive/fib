Illustration how badly works parallel version fibbonachi.

# build
g++ fib.cpp -lpthread
# parallel
time ./a.out
# sequentional
time ./a.out 2

# branch "master"
incorrect version, we do not count the threads overhead to initialization and join

# branch "right"
correct version, we count threads overhead
