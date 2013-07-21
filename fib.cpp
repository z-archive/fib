#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t res_mtx;

long fib(long n) {
    long i=2;
    long a=1;
    long b=1;
    while(i < n) {
        long c = a + b;
        a = b;
        b = c;
        ++i;
    }
    return b;
}

long val1, val2;

void *fib_worker_one(void *data)
{
    val1 = fib(*((long *) data));
    pthread_exit(NULL);
}
void *fib_worker_two(void *data)
{
    val2 = fib(*((long *) data));
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t t1, t2;
    pthread_attr_t attr;
    void *status;
    long n=5000;
    long v1 = n-1, v2 = n-2;
    long result;
    for(long r=0; r < 1000*1000; ++r) {
        if (argc == 2) {
            result = fib(n);
        } else {
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

            pthread_create(&t1, &attr, fib_worker_one, (void *) &v1);
            pthread_create(&t2, &attr, fib_worker_two, (void *) &v2);

            pthread_join(t1, &status);
            pthread_join(t2, &status);

            result = val1 + val2;
        }
    }
    std::cout << result << std::endl;

    return 0;
}
