#include <iostream>
#include <string>
#include "test.h"

using namespace std;

void test_are_equal(string description, string val1, string val2)
{
    if (val1 != val2)
        cout << description << ": " << val1 << " != " << val2 << endl;
}

void test_are_equal(string description, bool val1, bool val2)
{
    if (val1 != val2)
        cout << description << ": " << val1 << " != " << val2 << endl;
}

void test_are_equal(string description, double val1, double val2)
{
    if (val1 != val2)
        cout << description << ": " << val1 << " != " << val2 << endl;
}