#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "graph.h"
#include "algebra.h"
#include "number.h"

using namespace std;

extern Number N_2, N_0;

// init class methods
Number Range::length()
{
    return subtract(end, start);
}
bool Range::is_between(Number num, bool closed_start, bool closed_end)
{
    bool left_side = (closed_start ? is_greater_equal(num, start) : is_greater(num, start)),
         right_side = (closed_end ? is_smaller_equal(num, end) : is_smaller(num, end));

    return left_side && right_side;
}
// --------------

string replace_x_with(string exp, string repl)
{
    for (unsigned i = 0; i < exp.length(); i++)
        if (exp[i] == 'x')
            exp.replace(i, 1, repl);

    return exp;
}

void draw_graph(string expression, Range x_range, Number x_step, Range y_range, Number y_step)
{
    vector<Point> points;

    // extracting data
    for (Number x = x_range.start; is_smaller_equal(x, x_range.end); x = sum(x, x_step))
    {
        Number x1 = x, x2 = sum(x, x_step);
        string exp1 = replace_x_with(expression, x1.printable_string()),
               exp2 = replace_x_with(expression, x2.printable_string());

        try
        {
            Number
                y1 = get_answer(exp1),
                y2 = get_answer(exp2);

            Number y_mean = divide(sum(y1, y2), N_2);
            points.push_back(Point(x, y_mean));
        }
        catch (...)
        {
        }
    }

    // printing data
    for (Number y = y_range.end; is_greater_equal(y, y_range.start); y = subtract(y, y_step))
    {
        Range line_range(subtract(y, y_step), y);

        for (Number x = x_range.start; is_smaller_equal(x, x_range.end); x = sum(x, x_step))
        {
            bool is_match = false;
            for (unsigned i = 0; i < points.size(); i++)
            {
                if (are_equal(points[i].x, x) && line_range.is_between(points[i].y, false, true))
                {
                    is_match = true;
                    break;
                }
            }

            if (is_match)
                cout << '*';
            else if (are_equal(y, N_0))
                cout << '_';
            else if (are_equal(x, N_0))
                cout << '|';
            else
                cout << ' ';
        }

        cout << endl;
    }
}