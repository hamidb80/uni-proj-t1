#pragma once
#include "number.h"

const unsigned int MAX_ROWS = 5,
                   MAX_COLUMNS = 5;

class Matrix
{
public:
    int rows, columns;
    Number table[MAX_ROWS][MAX_COLUMNS];

    Matrix();
    Matrix(int _rows, int _columns, Number _table[MAX_ROWS][MAX_COLUMNS]);
};

// for both summation & subtraction
Matrix sum_sub(Matrix mat1, Matrix mat2, bool is_sum);
Matrix multiplicate(Matrix mat1, Matrix mat2);
Matrix taranahade(Matrix mat1);