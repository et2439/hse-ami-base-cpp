#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int a = 0;
    int b = static_cast<int>(str.size()) - 1;
    while (a < b) {
        while (a < b && str[a] == ' ') {
            ++a;
        }
        while (a < b && str[b] == ' ') {
            --b;
        }
        if (str[a] != str[b]) {
            return false;
        }
        ++a;
        --b;
    }

    return true;
}
