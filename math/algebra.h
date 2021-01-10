#pragma once
#include <string>
#include "number.h"

using namespace std;

class MyTuple
{
public:
    long int last_index;
    string value;
    string func_name;

    MyTuple(string _value, long int _last_index, string fname="");
};

bool is_numberic_char(char ch);
unsigned short int get_operator_priority(string ope);

MyTuple get_next_operator(string algebra);
MyTuple get_next_algebra(string algebra, short int last_operator_priority, bool is_first = false);

Number calculate(string ope, Number &n1);
Number calculate(string ope, Number &n1, Number &n2);
Number get_answer(string algebra);