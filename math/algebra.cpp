#include <string>
#include "algebra.h"
#include "number.h"

using namespace std;

class MyTuple
{
public:
    long int last_index;
    string value;
    // Tuple(int li, string val) last_index(li), value(val) {}
};

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

MyTuple get_next_operator(string &algebra, long int from)
{
    MyTuple result;

    for (long int i = from; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
        {

            // return algebra[i];
            return result;
        }

    return result;
}

MyTuple get_next_algebra(string &algebra, long int from, short int operator_priority)
{

    long int
        i = from + 1,
        first_range[2] = {from, -1};

    while (true)
    {
        if (algebra[i] == '\0')
        {
        }
    }
}

Number get_answer(string algebra)
{
    // char ope = get_first_operator(algebra);
    // short int pr = get_operator_priority(ope);

    Number n;
    return n;
}
