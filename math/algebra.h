#pragma once
#include <string>
#include "number.h"

using namespace std;

class NextAlgebraData
{
public:
    long int last_index;
    string value;
    string func_name;

    NextAlgebraData(string _value, long int _last_index, string fname = "")
    {
        value = _value;
        last_index = _last_index;
        func_name = fname;
    }
};

bool is_numberic_char(char ch);
unsigned short int get_operator_priority(char ope);

NextAlgebraData get_next_algebra(string algebra, short int last_operator_priority, bool is_first = false);

Number calculate(string ope, Number n1);
Number calculate(string ope, Number n1, Number n2);
Number get_answer(string algebra);