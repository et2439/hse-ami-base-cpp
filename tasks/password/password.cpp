#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int size_min = 8;
    const int size_max = 14;
    const int ascii_min = 33;
    const int ascii_max = 126;
    if (static_cast<int>(password.size()) < size_min || static_cast<int>(password.size()) > size_max) {
        return false;
    } else {
        int capitalized = 0;
        int non_capitalized = 0;
        int numbers = 0;
        int others = 0;
        for (int i = 0; i < static_cast<int>(password.size()); i++) {
            if (static_cast<int>(password[i]) < ascii_min || static_cast<int>(password[i]) > ascii_max) {
                return false;
            } else {
                if (isalpha(password[i])) {
                    isupper(password[i]) ? capitalized = 1 : non_capitalized = 1;
                } else if (isdigit(password[i])) {
                    numbers = 1;
                } else {
                    others = 1;
                }
            }
        }
        if (capitalized + non_capitalized + numbers + others < 3) {
            return false;
        }
    }
    return true;
}
