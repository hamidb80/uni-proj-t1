#include <string>
#include "algebra.h"

using namespace std;

bool is_numberic_char(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}

// does the math_setence have non-numberic chars ?
bool required_algebra_process(string math_sentence)
{
    for (int i = 0; i < math_sentence.length(); i++)
        if (is_numberic_char(math_sentence[i]))
            return true;

    return false;
}
