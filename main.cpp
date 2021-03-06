#include <iostream>
#include <string>
#include "math/number.h"
#include "math/matrix.h"
#include "math/algebra.h"
#include "math/graph.h"
#include "utils/string.h"
#include "test/tester.h"

#include "math/functions.h"

using namespace std;

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
         << endl

         << ">> Functions <<" << endl
         << "absolute          abs([number])" << endl
         << "factorial         fact([number])" << endl
         << "ceil              ceil([number])" << endl
         << "floor             floor([number])" << endl
         << "ln                ln([number])" << endl
         << "log               log([base], [number])" << endl
         << "log10             log([number])" << endl

         << "sin               sin([number])" << endl
         << "cos               cos([number])" << endl
         << "tan               tan([number])" << endl
         << "cot               cot([number])" << endl
         << "sec               sec([number])" << endl
         << "csc               csc([number])" << endl

         << "sinh              sinh([number])" << endl
         << "cosh              cosh([number])" << endl
         << "tanh              tanh([number])" << endl
         << "coth              coth([number])" << endl
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
            << "1. free algebra" << endl
            << "2. matrix " << endl
            << "3. graph " << endl
            << "4. show help " << endl
            << "[any other number]. exit " << endl;

        cin >> option;
        cin.ignore();

        if (option == 1)
        {
            cout << "enter your algebra: " << endl
                 << ">  ";

            string line;
            getline(cin, line);
            line = remove_spaces(line);

            try
            {
                cout << get_answer(line).printable_string() << endl;
            }
            catch (...)
            {
                cout << "Error: the expression is not valid." << endl;
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

            try
            {
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
            }
            catch (string e)
            {
                cerr << e << '\n';
            }

            show_matrix_in_stdout(result);
        }
        else if (option == 3)
        {
            cout << "enter your function: " << endl
                 << "y= ";

            string line;
            getline(cin, line);
            line = remove_spaces(line);

            string x_start, x_end, x_step,
                y_start, y_end, y_step;

            cout << "x start range: ";
            cin >> x_start;
            cout << "x end range: ";
            cin >> x_end;
            cout << "x step: ";
            cin >> x_step;

            cout << "y start range: ";
            cin >> y_start;
            cout << "y end range: ";
            cin >> y_end;
            cout << "y step: ";
            cin >> y_step;

            draw_graph(line,
                       Range(get_answer(x_start), get_answer(x_end)), get_answer(x_step),
                       Range(get_answer(y_start), get_answer(y_end)), get_answer(y_step));
        }
        else if (option == 4)
            show_help();
        else
            break;
    }
}