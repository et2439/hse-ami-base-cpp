#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t n1 = numerator;
    int64_t n2 = denominator;
    while (n1 != n2) {
        if (n1 > n2) {
            n1 -= n2;
        } else {
            n2 -= n1;
        }
    }
    return numerator / n1 + denominator / n1;
}
