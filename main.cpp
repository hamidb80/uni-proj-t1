#include <iostream>
#include <string>
#include "utils/test.h"
#include "math/number.h"
#include "math/algebra.h"

using namespace std;

string TRINGLE_FUNCTIONS_BASE = "DEG"; // DEG, RAD, GRAD

void test_number()
{
    Number
        n1("1"),
        n99_3("99.3"),
        n999("999"),
        n991("991"),
        n1000("1000");

    // greater test
    test_are_equal(
        "999 > 999",
        is_greater(n999, n999),
        false);

    test_are_equal(
        "999 > 991",
        is_greater(n999, n991),
        true);

    test_are_equal(
        "1000 > 999",
        is_greater(n1000, n999),
        true);

    test_are_equal(
        "991 > 99.3",
        is_greater(n991, n99_3),
        true);

    // summation test
    test_are_equal(
        "991 + 999 ",
        sum(Number("999"), Number("991")).printable_string(),
        "1990");

    test_are_equal(
        "991 + 00",
        sum(Number("999"), Number("0")).printable_string(),
        "999");

    test_are_equal(
        "999 + 999",
        sum(Number("999"), Number("999")).printable_string(),
        "1998");

    test_are_equal(
        "79.64 + 1.1",
        sum(Number("79.64"), Number("1.1")).printable_string(),
        "80.74");

    test_are_equal(
        "5.400 + 5.11",
        sum(Number("5.400"), Number("5.11")).printable_string(),
        "10.51");

    //"subtraction test"
    test_are_equal(
        "991 - 999",
        subtract(Number("991"), Number("999")).printable_string(),
        "-8");

    test_are_equal(
        "999 - 991",
        subtract(Number("999"), Number("991")).printable_string(),
        "8");

    test_are_equal(
        "10 - 10",
        subtract(Number("10"), Number("10")).printable_string(),
        "0");

    test_are_equal(
        "1201 - 991",
        subtract(Number("1201"), Number("991")).printable_string(),
        "210");

    test_are_equal(
        "79.64 - 1.1",
        subtract(Number("79.64"), Number("1.1")).printable_string(),
        "78.54");

    //"multipicataton test"
    test_are_equal(
        "24 * 67",
        multiplicate(Number("24"), Number("67")).printable_string(),
        "1608");

    test_are_equal(
        "999 * 999",
        multiplicate(Number("999"), Number("999")).printable_string(),
        "998001");

    test_are_equal(
        "79.64 * 79.64",
        multiplicate(Number("79.64"), Number("79.64")).printable_string(),
        "6342.5296");

    test_are_equal(
        "1.1 * 1.1",
        multiplicate(Number("1.1"), Number("1.1")).printable_string(),
        "1.21");

    test_are_equal(
        "79.64 * 1.1",
        multiplicate(Number("79.64"), Number("1.1")).printable_string(),
        "87.604");

    test_are_equal(
        "79.64 * 1",
        multiplicate(Number("79.64"), Number("1")).printable_string(),
        "79.64");

    test_are_equal(
        "46.300 * 0",
        multiplicate(Number("46.300"), Number("0")).printable_string(),
        "0");

    test_are_equal(
        "46.300 * 00",
        multiplicate(Number("46.300"), Number("00")).printable_string(),
        "0");

    test_are_equal(
        "1 * 4.5",
        multiplicate(Number("1"), Number("4.5")).printable_string(),
        "4.5");

    // "Number functionality"
    string old_n1 = n1.printable_string();
    n1.shift_digits_for(2);
    test_are_equal(
        old_n1 + " shift for 2 indexes",
        n1.printable_string(),
        "100");

    string new_n1 = n1.printable_string();
    n1.shift_digits_for(-2);
    test_are_equal(
        new_n1 + " shift for -2 indexes",
        n1.printable_string(),
        "1");

    // "division test";
}
void test_algebra()
{
}
void test_whole_all()
{
    cout << "--- Fails ---" << endl;

    test_number();
    test_algebra();

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
         << "power          ^" << endl
        //  << "factorial      !" << endl


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

    while (true)
    {
        short int option;
        cout
            << "What you want?" << endl
            << "0. set base unit for triabgle functons "
            << "[the current base is '" << TRINGLE_FUNCTIONS_BASE << "']" << endl
    
            << "1. free algebra" << endl
            << "2. matrix " << endl
            << "3. unit tranform " << endl
            << "4. graph " << endl
            << "[any other number]. exit " << endl;

        cin >> option;
        cin.ignore();

        if (option == 0)
        {
            // TODO: validate the input
            cout << "available bases are: " << "DEG, RAD, GRAD" << endl;
            cout << "the default base for triangle functions would be: " << endl;
            string new_base;
            cin >> new_base;

            TRINGLE_FUNCTIONS_BASE = new_base;
        }
        else if (option == 1)
        {
            show_help();

            cout << "enter your algebra: " << endl;

            string line;
            getline(cin, line);
        }
        else if (option == 2)
        {
            cout
                << "What you want?" << endl
                << "1. summation" << endl
                << "2. subtraction" << endl
                << "3. multipication" << endl
                << "4. transpose" << endl
                << "[any other number]. exit" << endl
                << "The number of the option: ";

            // enter matrix 1

            if (option >= 1 && option <= 3)
            {
                // enter matrix 2
                if (option == 1)
                {
                }
                else if (option == 2)
                {
                }
                else
                {
                }
            }
            else if (option == 4)
            {
            }
        }
        else if (option == 3)
        {
            string from_unit, to_unit,
                from_value, to_value;

            cout << "from unit: ";
            cin >> from_unit;

            cout << "to unit: ";
            cin >> to_unit;

            cout << "from value: ";
            cin >> from_value;

            Number
                from_value_number(from_value),
                to_value_number(to_value);
        }
        else if (option == 4)
        {
            cout << "enter your function: " << endl
                 << "y= ";

            string line;
            getline(cin, line);
        }
        else
            break;
    }

    cout << "-----------------" << endl;
}