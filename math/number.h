#pragma once
#include <string>
#include <vector>

using namespace std;

const unsigned short int
    KEEP_FLOAT_BEFORE = 10,
    FLOAT_CLEAR_AFTER = 5;

class Number
{
    /*
    the number stores with this pattern: 

    35.21 ->
        sign: 1
        digits: {3,5,2,1}
        float_point_i: 2

    -68 ->
        sign: 0
        digits: {6,8}
        float_point_i: 2
    */

public:
    vector<short int> digits;
    // 6 -> the float point is between 6th & 7th index of digits
    unsigned int float_point_i;
    bool sign; // 0 for -, 1 for +

    Number();
    Number(string str_num);

    // 12  shift digits for 2 => 1200,  12 shift digits for 1 => 1,
    void shift_digits_for(long int);
    void remove_float_after(short int num = FLOAT_CLEAR_AFTER);

    long int int_length();
    long int float_length();

    void clean();              // 04.0546000 => 04.0546
    string printable_string(); // "1.45"
    string raw_string();       // "001.4500"
};

// --- operations
Number sum(Number, Number);
Number subtract(Number, Number);
Number multiplicate(Number, Number);
Number divide(Number dividend, Number divisor, bool int_div = false);
struct DivRes
{
    Number qoutient, reminder;
    DivRes(Number _qoutient, Number _reminder) : qoutient(_qoutient), reminder(_reminder) {}
};
DivRes simple_divide(Number dividend, Number divisor); // 13/4 => 3, 12/4 => 3 uses for small divisions that thier answers is between 0 & 10

// --- comparation
bool is_greater(Number, Number);
bool are_equal(Number, Number);
bool is_smaller_equal(Number, Number);
bool is_smaller(Number, Number);
bool is_greater_equal(Number, Number);

// --- other functions
void sync_float_points(Number &n1, Number &n2); // 0.1 , 54 => 0.1 , 54.0
void sync_int(Number &n1, Number &n2);          // 15 , 1 => 15 , 01
void sync_num(Number &n1, Number &n2);          // sync_float_points & sync_int

Number split_digits(Number n1, long int from, long int to); // split digits from a number with a index range