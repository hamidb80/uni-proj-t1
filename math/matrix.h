#pragma once
#include "number.h"

const unsigned int
    MAX_ROWS = 5,
    MAX_COLUMNS = 5;

class Matrix
{
public:
    int rows, columns;
    Number table[MAX_ROWS][MAX_COLUMNS];

    Matrix();
    Matrix(int _rows, int _columns, Number _table[MAX_ROWS][MAX_COLUMNS]);
    string in_row_string();
};

// for both summation & subtraction
Matrix sum_sub(Matrix mat1, Matrix mat2, bool is_sum);
Matrix sum(Matrix mat1, Matrix mat2);
Matrix subtract(Matrix mat1, Matrix mat2);
Matrix multiplicate(Matrix mat1, Matrix mat2);
Matrix transpose(Matrix mat1);

// utils
Matrix get_matrix_from_stdin();
void show_matrix_in_stdout(Matrix &m);