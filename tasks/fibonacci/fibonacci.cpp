#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 1 || n == 0) {
        return n;
    } else {
        int64_t a = 0;
        int64_t b = 1;
        for (int64_t i = 2; i <= n; ++i) {
            int64_t c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
}
