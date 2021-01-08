#include <iostream>
#include <string>
#include "test.h"

using namespace std;

string bool_show(bool cond){
    return (cond ? "true" : "false");
}

void error_if_were_not_equal(string description, string val1, string val2)
{
    if (val1 != val2)
        cout << description << ": " << val1 << " != " << val2 << endl;
}

void error_if_were_not_equal(string description, bool val1, bool val2)
{
    if (val1 != val2)
        cout << description << ": " << bool_show( val1) << " != " << bool_show(val2) << endl;
}