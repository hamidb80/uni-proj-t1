#include <iostream>
#include <string>
#include "utils/test.h"
#include "math/number.h"

using namespace std;

void test_whole_all()
{
    cout << "--- Errors ---" << endl;

    Number
        n0,
        n00("0.00", "10"),
        n1("1201", "10"),
        n2("991", "10"),
        n3("999", "10"),
        n4("79.64", "10"),
        n5("1.1", "10"),
        n6("1", "10"),
        n7("5.400", "10"),

        n8("24", "10"),
        n9("67", "10");

    // greater test
    test_are_equal(
        n3.printable_string() + " > " + n4.printable_string(),
        is_greater(n3, n4), true);
    test_are_equal(
        n2.printable_string() + " > " + n3.printable_string(),
        is_greater(n2, n3), false);

    //"summation test"
    test_are_equal(
        n2.printable_string() + " + " + n3.printable_string(),
        sum(n2, n3).printable_string(), "1990");
    test_are_equal(
        n3.printable_string() + " + " + n2.printable_string(),
        sum(n3, n2).printable_string(), "1990");
    test_are_equal(
        n2.printable_string() + " + " + n1.printable_string(),
        sum(n2, n1).printable_string(), "2192");
    test_are_equal(
        n3.printable_string() + " + " + n3.printable_string(),
        sum(n3, n3).printable_string(), "1998");
    test_are_equal(
        n4.printable_string() + " + " + n5.printable_string(),
        sum(n4, n5).printable_string(), "80.74");
    test_are_equal(
        n7.printable_string() + " + " + n3.printable_string(),
        sum(n7, n3).printable_string(), "1004.4");

    //"subtraction test"
    test_are_equal(
        n2.printable_string() + " - " + n3.printable_string(),
        subtract(n2, n3).printable_string(), "-8");
    test_are_equal(
        n3.printable_string() + " - " + n2.printable_string(),
        subtract(n3, n2).printable_string(), "8");
    test_are_equal(
        n3.printable_string() + " - " + n3.printable_string(),
        subtract(n3, n3).printable_string(), "0");
    test_are_equal(
        n2.printable_string() + " - " + n1.printable_string(),
        subtract(n2, n1).printable_string(), "-210");
    test_are_equal(
        n4.printable_string() + " - " + n5.printable_string(),
        subtract(n4, n5).printable_string(), "78.54");

    //"multipicataton test"
    test_are_equal(
        n8.printable_string() + " * " + n9.printable_string(),
        multiplicate(n8, n9).printable_string(), "1608");
    test_are_equal(
        n3.printable_string() + " * " + n3.printable_string(),
        multiplicate(n3, n3).printable_string(), "998001");
    test_are_equal(
        n4.printable_string() + " * " + n4.printable_string(),
        multiplicate(n4, n4).printable_string(), "6342.5296");
    test_are_equal(
        n5.printable_string() + " * " + n5.printable_string(),
        multiplicate(n5, n5).printable_string(), "1.21");
    test_are_equal(
        n4.printable_string() + " * " + n5.printable_string(),
        multiplicate(n4, n5).printable_string(), "87.604");
    test_are_equal(
        n4.printable_string() + " * " + n0.printable_string(),
        multiplicate(n4, n0).printable_string(), "0");
    test_are_equal(
        n4.printable_string() + " * " + n00.printable_string(),
        multiplicate(n4, n00).printable_string(), "0");
    test_are_equal(
        n6.printable_string() + " * " + n2.printable_string(),
        multiplicate(n6, n2).printable_string(), n2.printable_string());


    // "Number functionality"
    string old_n6 = n6.printable_string();
    n6.shift_digits_for(2);
    test_are_equal(
        old_n6 + " shift for 2 indexes",
        n6.printable_string(), "100");

    string new_n6 = n6.printable_string();
    n6.shift_digits_for(-2);
    test_are_equal(
        new_n6 + " shift for -2 indexes",
        n6.printable_string(), "1");

    // "division test";

    cout << "--- APP TESTED ---" << endl;
}
void show_help()
{
    cout << endl
         << "::::::::::::: SIMPLE CALC :::::::::::::" << endl
         << endl

         << ">>> FEATURES <<<" << endl
         << "$ algebra things: -sinh(3) + log(10*(3-2)*ln(2))" << endl
         << "$ large number" << endl
         << endl

         << ">>> SYNTAX GUIDE <<<" << endl
         << endl

         << ">> Constants <<" << endl
         << "p:     as pi number for circle" << endl
         << "e:     as neper number" << endl
         << endl

         << ">> Operators <<" << endl
         << "summation      +" << endl
         << "subtraction    -" << endl
         << "multipication  *" << endl
         << "division       /" << endl
         << "power          ^ -> base^number" << endl

         << ">> Functions <<" << endl
         << "log               log(base, number)" << endl
         << "ln (natural log)  ln(number)" << endl
         << "absolute          abs(number)" << endl
         << "factorial         fact(number)" << endl
         //  << "radic             radic(base, number)" << endl
         << "ceil              ceil()" << endl
         << "floor             floor()" << endl

         << "sin               sin()" << endl
         << "cos               cos()" << endl
         << "tan               tan()" << endl
         << "cot               cot()" << endl
         << "sinh              sinh()" << endl
         << "cosh              cosh()" << endl
         << "tanh              tanh()" << endl
         << "coth              coth()" << endl

         << "arcsin            arcsin()" << endl
         << "arccos            arccos()" << endl
         << "arctan            arctan()" << endl
         << "arccot            arccot()" << endl
         << "arcsinh           arcsinh()" << endl
         << "arccosh           arccosh()" << endl
         << "arctanh           arctanh()" << endl
         << "arccoth           arccoth()" << endl
         << endl;
}

int main()
{
    test_whole_all();

    string line;
    while (line != "exit")
    {
        getline(cin, line);
    }
}