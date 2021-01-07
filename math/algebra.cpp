#include <string>
#include "algebra.h"
#include "number.h"
#include "functions.h"

using namespace std;

MyTuple::MyTuple(string _value, long int _last_index)
{
    value = _value;
    last_index = _last_index;
}

bool is_numberic_char(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}

unsigned short int get_operator_priority(string ope)
{
    /*
    Character   | Priority
    0-9  \0     | 0
    - +         | 1
    * /         | 2
    ^ ! func()  | 3
    ()          | 4
    */

    if (ope == "-" || ope == "+")
        return 1;

    else if (ope == "*" || ope == "/")
        return 2;

    else if (ope == "^" || ope == "!")
        return 3;

    else
        return 4;
}

MyTuple get_next_operator(string algebra)
{
    for (long int i = 0; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
            return MyTuple(string(1, algebra[i]), i);

    return MyTuple("none", -1);
}
MyTuple get_next_algebra(string algebra, short int last_operator_priority)
{
    long int i = 0;

    for (; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
        {
            short int operator_priority = get_operator_priority(string(1, algebra[i]));

            if (operator_priority == 0 || operator_priority <= last_operator_priority)
                return MyTuple(algebra.substr(0, i), i);
        }

    return MyTuple(algebra, algebra.length());
}

Number calculate(string ope, Number n1, Number n2)
{
    if (ope == "+")
        return sum(n1, n2);

    else if (ope == "-")
        return subtract(n1, n2);

    else if (ope == "*")
        return multiplicate(n1, n2);

    else if (ope == "/")
        return divide(n1, n2);

    else if (ope == "^")
        return pow(n1, n2);

    else if (ope == "!")
    {
    }
    else
    {
        // throw
    }

    // else if (ope == "sin")
    // {
    // }

    return n1;
}
Number get_answer(string algebra)
{
    unsigned long int i = 0;

    string nextt = get_next_algebra(algebra, 5).value;
    Number first_number(nextt);

    while (i < algebra.length())
    {
        MyTuple opera = get_next_operator(algebra.substr(i));

        if (opera.value == "none")
            break;

        short int opera_pr = get_operator_priority(opera.value);

        i += opera.last_index + 1;

        MyTuple second_algebra = get_next_algebra(algebra.substr(i), opera_pr);

        first_number = calculate(opera.value, first_number, get_answer(second_algebra.value));

        i += second_algebra.last_index;
    }

    return first_number;
}