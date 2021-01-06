#include <string>
#include "algebra.h"
#include "number.h"

using namespace std;

bool is_numberic_char(char ch)
{
    return (ch >= '0' && ch <= '9') || ch == '.';
}

unsigned short int get_operator_priority(char ope)
{
    /*
    Character   | Priority
    0-9  \0     | 0
    - +         | 1
    * /         | 2
    ^ ! func()  | 3
    ()          | 4
    */

    switch (ope)
    {
    case '-':
    case '+':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
    case '!':
        return 3;

    default:
        return 4;
    }
}

long int get_next_operator_index(string &algebra, long int from)
{
    for (long int i = from; i < algebra.length(); i++)
        if (!is_numberic_char(algebra[i]))
            return algebra[i];

    return '~';
}

long int get_next_algebra_last_index(string &algebra, long int from, short int operator_priority)
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
