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
// TODO: seprate MyTuple from next_algebra & next_operator
class Arguments
{
public:
    string arg1, arg2;

    Arguments(string _arg1 = "", string _arg2 = "")
    {
        arg1 = _arg1;
        arg2 = _arg2;
    }
};

Arguments get_arguments(string inside_pars)
{
    short int depth = 0;

    for (unsigned i = 0; i < inside_pars.length(); i++)
    {
        if (inside_pars[i] == '(')
            depth++;
        else if (inside_pars[i] == ')')
            depth--;

        else if (depth == 0 && inside_pars[i] == ',')
            return Arguments(inside_pars.substr(0, i), inside_pars.substr(i + 1));
    }

    return Arguments(inside_pars);
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

Number get_var(string var_name)
{
    if (var_name == "e")
        return E;
    else if (var_name == "p")
        return P;

    // TODO make all errors like this
    __throw_domain_error("the var is not exists");
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

    else if (ope == "stick")
        return Number(n1.printable_string() + n2.printable_string());

    throw "not matched";
}
Number calculate(string func_name, Number n1)
{
    if (func_name == "fact")
        return fact(n1);
    if (func_name == "abs")
        return abs(n1);
    else if (func_name == "floor")
        return floor(n1);
    else if (func_name == "ceil")
        return ceil(n1);

    else if (func_name == "sin")
        return sin(n1);
    else if (func_name == "cos")
        return cos(n1);
    else if (func_name == "sec")
        return sec(n1);
    else if (func_name == "csc")
        return csc(n1);
    else if (func_name == "tan")
        return tan(n1);
    else if (func_name == "cot")
        return cot(n1);

    else if (func_name == "sinh")
        return sinh(n1);
    else if (func_name == "cosh")
        return cosh(n1);
    else if (func_name == "tanh")
        return tanh(n1);
    else if (func_name == "coth")
        return coth(n1);

    return get_var(func_name);
}

unsigned short int get_operator_priority(string ope)
{
    /* Character   | Priority
       - +         | 1
       * /         | 2
       ^ func()    | 3 */

    if (ope == "-" || ope == "+")
        return 1;

    else if (ope == "*" || ope == "/")
        return 2;

    else if (ope == "^")
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
    string funcname = "";

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

        else if (depth == 0)
        {
            if (is_alphabet(algebra[i]))
            {
                if (!matched)
                {
                    // get the whole word
                    for (; i < algebra.length() && is_alphabet(algebra[i]); i++)
                        funcname += algebra[i];

                    // if it wasn't function, assume it as a number
                    if (algebra[i] != '(')
                        matched = true;

                    i--;
                }
                // if there was more than 1 word, assume them as numbers
                else
                    funcname = "";
            }
            else if (!is_numberic(algebra[i]))
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

        // match everything between pars
        else
            matched = true;
    }

    if (depth != 0)
        throw "depth error";

    // --------

    bool is_function_call = (funcname != "" && pars == 1 && algebra[algebra.length() - 1] == ')');
    bool is_var_call = (funcname != "" && algebra.substr(0, i) == funcname);
    string scope;

    if (is_function_call)
        scope = algebra.substr(funcname.length(), i - funcname.length());
    else
    {
        if (!is_var_call)
        {
            funcname = "";
            scope = algebra.substr(0, i);
        }
    }
    return MyTuple((pars == 1 ? remove_pars(scope) : scope), i - 1, funcname);
}

Number get_answer(string algebra)
{
    MyTuple opera("@", -1);
    Number result;
    bool is_first = true;

    unsigned long int i = 0;
    while (i < algebra.length())
    {
        MyTuple next_algebra = get_next_algebra(algebra.substr(i), (is_first ? 4 : get_operator_priority(opera.value)), is_first);
        Number next_result;

        if (next_algebra.func_name != "")
        {
            Arguments args = get_arguments(next_algebra.value);

            if (args.arg2 == "")
                next_result = calculate(next_algebra.func_name, get_answer(args.arg1));
            else
                next_result = calculate(next_algebra.func_name, get_answer(args.arg1), get_answer(args.arg2));
        }
        else if (is_pure_number(next_algebra.value))
            next_result = Number(next_algebra.value);
        else
            next_result = get_answer(next_algebra.value);

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