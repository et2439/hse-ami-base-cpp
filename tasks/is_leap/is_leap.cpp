#include "is_leap.h"

bool IsLeap(int year) {
    const int c1 = 4;
    const int c2 = 100;
    const int c3 = 400;
    return (((year % c1 == 0) && (year % c2 != 0)) || (year % c3 == 0));
}
