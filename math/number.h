#pragma once
#include <string>

using namespace std;

const unsigned short int
    FLOAT_CLEAR_AFTER = 5,
    MAX_DIGITS = 500; // FIXME: increase this to 10e+5

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

    // digits: 12 indexes: 2 => 1200, digits: 12 indexes: -1 => 1
    void shift_digits_for(int indexes);
    void remove_float_after(short int num);

    long int int_length();
    long int float_length();

    // 4.0546000 => 4.0546
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
Number divide(Number dividend, Number divisor, bool int_div = false);
DivRes simple_divide(Number dividend, Number divisor);

// --- comparation
bool is_greater(Number n1, Number n2);
bool are_equal(Number n1, Number n2);
bool is_smaller_equal(Number n1, Number n2);
bool is_smaller(Number n1, Number n2);
bool is_greater_equal(Number n1, Number n2);

// --- other functions
void sync_float_points(Number &n1, Number &n2);
Number split_digits(Number n1, long int from, long int to);