#include <iostream>
#include <string>
#include "math/number.h"
#include "math/matrix.h"
#include "math/algebra.h"
#include "utils/string.h"
#include "test/tester.h"

#include "math/functions.h"

using namespace std;

string TRINGLE_FUNCTIONS_BASE = "DEG"; // DEG, RAD, GRAD

void show_help()
{
    cout << endl
         << "::::::::::::: SIMPLE CALC :::::::::::::" << endl
         << endl

         << ">>> FEATURES <<<" << endl
         << "$ free algebra: -sinh(3) + sin(10^(3-2)*ln(2))" << endl
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
         << "factorial      !" << endl
         << endl

         << ">> Functions <<" << endl
         << "ln (natural log)  ln([number])" << endl
         //  << "log               log([base], [number])" << endl
         << "absolute          abs([number])" << endl
         << "factorial         fact([number])" << endl
         << "ceil              ceil([number])" << endl
         << "floor             floor([number])" << endl
         //  << "radic             radic(base, number)" << endl

         << "sin               sin([number])" << endl
         << "cos               cos([number])" << endl
         << "tan               tan([number])" << endl
         << "cot               cot([number])" << endl
         << "sinh              sinh([number])" << endl
         << "cosh              cosh([number])" << endl
         << "tanh              tanh([number])" << endl
         << "coth              coth([number])" << endl

         << "arcsin            arcsin([number])" << endl
         << "arccos            arccos([number])" << endl
         << "arctan            arctan([number])" << endl
         << "arccot            arccot([number])" << endl
         << "arcsinh           arcsinh([number])" << endl
         << "arccosh           arccosh([number])" << endl
         << "arctanh           arctanh([number])" << endl
         << "arccoth           arccoth([number])" << endl
         << endl;
}

int main()
{
    test_entire_app();

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
            << "5. show help " << endl
            << "[any other number]. exit " << endl;

        cin >> option;
        cin.ignore();

        if (option == 0)
        {
            // TODO: validate the input
            cout << "available bases are: "
                 << "DEG, RAD, GRAD" << endl;
            cout << "the default base for triangle functions would be: " << endl;

            string new_base;
            cin >> new_base;

            TRINGLE_FUNCTIONS_BASE = new_base;
        }
        else if (option == 1)
        {
            cout << "enter your algebra: " << endl;

            string line;
            getline(cin, line);
            line = remove_spaces(line);

            try
            {
                cout << get_answer(line).printable_string() << endl;
            }
            catch (...)
            {
                cout << "Error: this expression is not valid." << endl;
            }
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

            cin >> option;
            cin.ignore();

            cout << "enter matrix info:" << endl;

            Matrix m1 = get_matrix_from_stdin(),
                   result;

            if (option >= 1 && option <= 3)
            {
                cout << "enter matrix info:" << endl;
                Matrix m2 = get_matrix_from_stdin();

                if (option == 1)
                    result = sum(m1, m2);
                else if (option == 2)
                    result = subtract(m1, m2);
                else
                    result = multiplicate(m1, m2);
            }
            else if (option == 4)
                result = transpose(m1);

            show_matrix_in_stdout(result);
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
            line = remove_spaces(line);
        }
        else if (option == 5)
            show_help();
        else
            break;
    }
}