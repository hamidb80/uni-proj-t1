#include "number.h"
#include "matrix.h"

using namespace std;

// constructors
Matrix::Matrix()
{
    rows = columns = 0;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
            table[y][x] = Number("0", "10");
}
Matrix::Matrix(int _rows, int _columns, Number _table[MAX_ROWS][MAX_COLUMNS])
{
    rows = _rows;
    columns = _columns;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
            table[y][x] = _table[y][x];
}

// operations
Matrix sum_sub(Matrix mat1, Matrix mat2, bool is_sum)
{
    Matrix mat3;

    // proc mat3
    for (int y = 0; y < mat1.rows; y++)
    {
        for (int x = 0; x < mat1.columns; x++)
            if (is_sum)
                mat3.table[y][x] = sum(mat1.table[y][x], mat2.table[y][x]);
            else
                mat3.table[y][x] = subtract(mat1.table[y][x], mat2.table[y][x]);
    }

    return mat3;
}
Matrix multiplicate(Matrix mat1, Matrix mat2)
{
    Matrix mat3;

    // proc mat3
    for (int y = 0; y < mat1.rows; y++)
    {
        for (int x = 0; x < mat2.columns; x++)
        {
            Number _sum("0", "10");

            for (int c = 0; c < mat1.columns; c++)
                _sum = sum(_sum, multiplicate(
                                     mat1.table[y][c], mat2.table[c][x]));

            mat3.table[y][x] = _sum;
        }
    }

    return mat3;
}
// Matrix taranahade(Matrix mat) {}