#include "utils.h"
#include <cctype>

bool containsText(const std::string& input) {
    for (char c : input) {
        if (!std::isdigit(c)) { // if character is not a digit
            return true; // contains text
        }
    }
    return false; // only digits
}
