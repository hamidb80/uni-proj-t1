#pragma once
#include <string>

using namespace std;

const unsigned short int
    FLOAT_CLEAR_AFTER = 5,
    MAX_DIGITS = 100; // FIXME: increase this to 10e+5

class Number
{
    /*
    the number stores with this pattern: 

    35.21 ->
        sign: 1
        digits: {0,0,0,...,3,5,2,1}
        float_point_i: MAX_DIGITS - 2

    -68 ->
        sign: 0
        digits: {0,0,0,...,6,8}
        float_point_i: MAX_DIGITS;
    */

public:
    short int digits[MAX_DIGITS] = {0};
    // 6 -> the float point is between 6th & 7th index of digits
    unsigned int float_point_i;
    string base; // <number> | rad | deg | grad
    bool sign;   // 0 for -, 1 for +

    Number();
    Number(string str_num, string _base = "10");

    // 4.0546000 => 4.0546
    void shift_digits_for(int indexes);

    unsigned int int_length();
    unsigned int float_length();

    void clean_float();
    string printable_string();
};

struct DivRes
{
    Number qoutient, reminder;
    DivRes(Number _qoutient, Number _reminder);
};

// --- operations
Number sum(Number n1, Number n2);
Number subtract(Number n1, Number n2);
Number multiplicate(Number n1, Number n2);
Number divide(Number n1, Number n2);
DivRes simple_divide(Number dividend, Number divisor);
// Number mod(Number n1, Number n2);

// --- comparation
bool is_greater(Number n1, Number n2);
bool are_equal(Number n1, Number n2);

// --- other functions
void sync_float_points(Number &n1, Number &n2);
Number split_digits(Number n1, long int from, long int to);