#pragma once
#include "number.h"

class Range
{
public:
    Number start, end;
    Range(Number _start, Number _end);
    Number length();
    bool is_between(Number num, bool start_closed = true, bool end_closed = false);
};

class Point
{
public:
    Number x, y;
    Point();
    Point(Number x, Number y);
};

void draw_graph(string expression, Range x_range, Number x_step, Range y_range, Number y_step);