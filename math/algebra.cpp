#include <string>
#include <vector>

#include "algebra.h"
#include "number.h"
#include "functions.h"

using namespace std;

extern Number E, P;

vector<string> get_arguments(string inside_pars)
{
    vector<string> res;

    if (inside_pars == "")
        return res;

    short int depth = 0;
    unsigned last_cut = 0;
    for (unsigned i = 0; i <= inside_pars.length(); i++)
    {

        if (i == inside_pars.length() || depth == 0 && inside_pars[i] == ',')
        {
            res.push_back(inside_pars.substr(last_cut, i - last_cut + 1));
            last_cut = i + 1;
        }

        else if (inside_pars[i] == '(')
            depth++;
        else if (inside_pars[i] == ')')
            depth--;
    }

    return res;
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

// "43+(2)" => "43+(2)", "(2+2)" => "2+2"
string remove_pars(string str)
{
    if (str[0] == '(' && str[str.length() - 1] == ')')
        str = str.substr(1, str.length() - 2);

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
Number calculate(char ope, Number n1, Number n2)
{
    if (ope == '+')
        return sum(n1, n2);

    else if (ope == '-')
        return subtract(n1, n2);

    else if (ope == '*')
        return multiplicate(n1, n2);

    else if (ope == '/')
        return divide(n1, n2);

    else if (ope == '^')
        return pow(n1, n2);

    throw "not matched";
}
Number calculate(string ope, Number n1, Number n2)
{
    if (ope == "stick")
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

unsigned short int get_operator_priority(char ope)
{
    /* Character   | Priority
       - +         | 1
       * /         | 2
       ^ func()    | 3 */

    if (ope == '-' || ope == '+')
        return 1;

    else if (ope == '*' || ope == '/')
        return 2;

    else if (ope == '^')
        return 3;

    throw "not matched";
}

NextAlgebraData get_next_algebra(string algebra, short int last_operator_priority, bool want_left_number)
{
    long int i = 0;
    unsigned int
        depth = 0, // depth of pars
        pars = 0;  // how many pars exists in this expression (algebra)?

    bool matched = false; // is any number matched so far?
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
                // if there was more than 1 word, assume they are numbers
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
                        if (want_left_number)
                            return NextAlgebraData("0", -1);

                        continue;
                    }

                    else
                        throw "err";
                }
                else
                {
                    short int operator_priority = get_operator_priority(algebra[i]);

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

    bool is_function_call = (funcname != "" && pars == 1 && algebra[algebra.length() - 1] == ')'),
         is_var_call = (funcname != "" && algebra.substr(0, i) == funcname);

    string scope; // algebra inside the pars or itself

    if (is_function_call)
        scope = algebra.substr(funcname.length(), i - funcname.length());
    else if (!is_var_call)
    {
        funcname = "";
        scope = algebra.substr(0, i);
    }

    return NextAlgebraData((pars == 1 ? remove_pars(scope) : scope), i - 1, funcname);
}

Number get_answer(string algebra)
{
    char opera = '+';
    Number result;
    bool is_first = true;

    unsigned long int i = 0;
    while (i < algebra.length())
    {
        NextAlgebraData next_algebra = get_next_algebra(algebra.substr(i), (is_first ? 4 : get_operator_priority(opera)), is_first);
        Number next_result;

        if (next_algebra.func_name != "")
        {
            vector<string> args = get_arguments(next_algebra.value);

            if (args.size() == 0)
                next_result = get_var(next_algebra.func_name);
            else if (args.size() == 1)
                next_result = calculate(next_algebra.func_name, get_answer(args[0]));
            else
                next_result = calculate(next_algebra.func_name, get_answer(args[0]), get_answer(args[1]));
        }
        else if (is_pure_number(next_algebra.value))
            next_result = Number(next_algebra.value);
        else
            next_result = get_answer(next_algebra.value);

        result = calculate(opera, result, next_result);
        i += next_algebra.last_index + 1;

        opera = algebra[i];

        i++;
        is_first = false;
    }

    return result;
}