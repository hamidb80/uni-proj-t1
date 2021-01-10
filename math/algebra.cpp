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

bool is_sign(char ch)
{
    return (ch == '-' || ch == '+');
}
bool is_numberic_char(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}
bool is_pure_number(string algebra)
{
    for (unsigned i = 0; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
            return false;

    return true;
}

string remove_around(string str)
{
    return str.substr(1, str.length() - 2);
}
string remove_pars(string str)
{
    if (str[0] == '(' && str[str.length() - 1] == ')')
        str = remove_around(str);

    return str;
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

    // else if (ope == "log")
    // {
    // }

    throw "not matched";
}
Number calculate(string ope, Number n1)
{
    if (ope == "fact")
    {
    }
    else if (ope == "floor")
    {
    }
    else if (ope == "ceil")
    {
    }

    else if (ope == "sin")
    {
    }
    else if (ope == "cos")
    {
    }
    else if (ope == "tan")
    {
    }
    else if (ope == "cot")
    {
    }

    else if (ope == "sinh")
    {
    }
    else if (ope == "cosh")
    {
    }
    else if (ope == "tanh")
    {
    }
    else if (ope == "coth")
    {
    }

    throw "not matched";
}

unsigned short int get_operator_priority(string ope)
{
    /*
    Character   | Priority
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

    throw "not matched";
}
MyTuple get_next_operator(string algebra)
{
    for (long int i = 0; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
            return MyTuple(string(1, algebra[i]), i);

    return MyTuple("none", -1);
}

MyTuple get_next_algebra(string algebra, short int last_operator_priority, bool is_first)
{
    long int i = 0;
    unsigned int depth = 0;
    bool matched = false;

    for (; i < algebra.length(); i++)
    {
        if (algebra[i] == '(')
            depth++;

        else if (algebra[i] == ')')
        {
            depth--;

            if (depth < 0)
            {
                throw 5;
                // throw "depth error";
            }
        }

        else if (!is_numberic_char(algebra[i]) && depth == 0)
        {
            if (matched == false)
            {
                // "---1" for example
                if (is_sign(algebra[i]))
                {
                    if (is_first)
                        return MyTuple("0", -1);

                    continue;
                }
                else
                    throw "err";
            }

            short int operator_priority = get_operator_priority(string(1, algebra[i]));

            if (operator_priority <= last_operator_priority)
            {
                return MyTuple(remove_pars(algebra.substr(0, i)), i - 1);
            }
        }
        else
            matched = true;
    }

    if (depth != 0)
        throw "depth error";

    return MyTuple(remove_pars(algebra), algebra.length());
}

Number get_answer(string algebra)
{
    MyTuple first_algebra = get_next_algebra(algebra, 4, true);
    Number first_number = (is_pure_number(first_algebra.value) ? Number(first_algebra.value) : get_answer(first_algebra.value));

    unsigned long int i = first_algebra.last_index + 1;

    while (i < algebra.length())
    {
        MyTuple opera = get_next_operator(algebra.substr(i));

        if (opera.value == "none")
            break;

        i += opera.last_index + 1;
        MyTuple second_algebra = get_next_algebra(algebra.substr(i), get_operator_priority(opera.value));

        first_number = calculate(opera.value, first_number, get_answer(second_algebra.value));
        i += second_algebra.last_index + 1;
    }

    return first_number;
}