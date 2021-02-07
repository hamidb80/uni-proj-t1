#include <iostream>
#include <string>
#include "test.h"
#include "../math/number.h"

using namespace std;

string bool_show(bool cond)
{
    return (cond ? "true" : "false");
}

void error_if_were_not_equal(string description, string val1, string val2)
{
    if (val1 != val2)
        cout << description << ": " << val1 << " != " << val2 << endl;
}

void error_if_were_not_equal(string description, Number n1, Number n2)
{
    if (n1.printable_string() != n2.printable_string())
        cout << description << ": " << n1.printable_string() << " != " << n2.printable_string() << endl;
}
void error_if_were_not_equal(string description, Matrix m1, Matrix m2)
{
    if (m1.rows != m2.rows || m1.columns != m2.columns || m1.in_row_string() != m2.in_row_string())
        cout << description << ": " << m1.in_row_string() << " != " << m2.in_row_string() << endl;
}

void error_if_were_not_equal(string description, Number n1, string ans)
{
    if (n1.printable_string() != ans)
        cout << description << ": " << n1.printable_string() << " != " << ans << endl;
}

void error_if_were_not_equal(string description, bool val1, bool val2)
{
    if (val1 != val2)
        cout << description << ": " << bool_show(val1) << " != " << bool_show(val2) << endl;
}