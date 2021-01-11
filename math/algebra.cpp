#include <string>
#include "algebra.h"
#include "number.h"
#include "functions.h"

using namespace std;

extern Number E, P;

MyTuple::MyTuple(string _value, long int _last_index, string fname)
{
    value = _value;
    last_index = _last_index;
    func_name = fname;
}

bool is_alphabet(char ch)
{
    return (ch >= 'a' && ch <= 'z');
}
bool is_sign(char ch)
{
    return (ch == '-' || ch == '+');
}
bool is_numberic(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}
bool is_pure_number(string algebra)
{
    for (unsigned i = 0; i < algebra.length(); i++)
        if (!is_numberic(algebra[i]))
            return false;

    return true;
}

// ".ds." => "ds"
string remove_around(string str)
{
    return str.substr(1, str.length() - 2);
}
// "43+(2)" => "43+(2)", "(2+2)" => "2+2"
string remove_pars(string str)
{
    if (str[0] == '(' && str[str.length() - 1] == ')')
        str = remove_around(str);

    return str;
}

// TODO:
Number get_var(string var_name)
{
    if (var_name == "e")
        return E;
    else if (var_name == "p")
        return P;

    throw "not match";
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
    // return log(n1);

    throw "not matched";
}
Number calculate(string ope, Number n1)
{
    if (ope == "fact")
        return fact(n1);
    if (ope == "abs")
        return abs(n1);
    else if (ope == "floor")
        return floor(n1);
    else if (ope == "ceil")
        return ceil(n1);

    else if (ope == "sin")
        return sin(n1);
    else if (ope == "cos")
        return cos(n1);
    else if (ope == "sec")
        return sec(n1);
    else if (ope == "csc")
        return csc(n1);
    else if (ope == "tan")
        return tan(n1);
    else if (ope == "cot")
        return cot(n1);

    else if (ope == "sinh")
        return sinh(n1);
    else if (ope == "cosh")
        return cosh(n1);
    else if (ope == "tanh")
        return tanh(n1);
    else if (ope == "coth")
        return coth(n1);

    throw "not matched";
}

// get_arguments log(2, 4*3)
// function
unsigned short int get_operator_priority(string ope)
{
    /* Character   | Priority
       - +         | 1
       * /         | 2
       ^ ! func()  | 3
       ()          | 4 */

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
        if (!is_numberic(algebra[i]))
            return MyTuple(string(1, algebra[i]), i);

    return MyTuple("none", -1);
}

MyTuple get_next_algebra(string algebra, short int last_operator_priority, bool is_first)
{
    long int i = 0;
    unsigned int
        depth = 0, // depth of pars
        pars = 0;  // how many pars exists in this expression (algebra)?
    bool matched = false;
    string funcname = "", scope = "";

    for (; i < algebra.length(); i++)
    {
        if (algebra[i] == '(')
            depth++;

        else if (algebra[i] == ')')
        {
            depth--;

            if (depth == 0)
                pars++;

            else if (depth < 0)
                throw "depth error";
        }

        else if (!is_numberic(algebra[i]) && depth == 0)
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
                else if (is_alphabet(algebra[i]))
                    funcname += algebra[i];
                else
                    throw "err";
            }
            else
            {
                short int operator_priority = get_operator_priority(string(1, algebra[i]));

                if (operator_priority <= last_operator_priority)
                    break;
            }
        }
        else
            matched = true;
    }

    if (depth != 0)
        throw "depth error";

    // --------
    bool is_func_call = (pars == 1 && funcname != "" && algebra[algebra.length() - 1] == ')');

    if (is_func_call)
        scope = algebra.substr(funcname.length(), i - funcname.length());
    else
    {
        scope = algebra.substr(0, i);
        funcname = "";
    }

    return MyTuple((pars == 1 ? remove_pars(scope) : scope), i - 1, funcname);
}

// TODO: multi argument
Number get_answer(string algebra)
{
    unsigned long int i = 0;
    MyTuple opera("+", -1);
    Number result;
    bool is_first = true;

    while (i < algebra.length())
    {
        MyTuple next_algebra = get_next_algebra(algebra.substr(i), (is_first ? 4 : get_operator_priority(opera.value)), is_first);
        Number next_result;

        if (is_pure_number(next_algebra.value))
            next_result = Number(next_algebra.value);
        else
            next_result = get_answer(next_algebra.value);

        if (next_algebra.func_name != "")
            next_result = calculate(next_algebra.func_name, next_result);

        result = (is_first ? next_result : calculate(opera.value, result, next_result));
        i += next_algebra.last_index + 1;

        opera = get_next_operator(algebra.substr(i));

        if (opera.value == "none")
            break;

        i += opera.last_index + 1;
        is_first = false;
    }

    return result;
}