#include "number.h"
#include "matrix.h"
#include <iostream>

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
        {
            if (is_sum)
                mat3.table[y][x] = sum(mat1.table[y][x], mat2.table[y][x]);
            else
                mat3.table[y][x] = subtract(mat1.table[y][x], mat2.table[y][x]);
        }
    }

    mat3.columns = mat1.columns;
    mat3.rows = mat1.rows;
    return mat3;
}
Matrix sum(Matrix mat1, Matrix mat2)
{
    return sum_sub(mat1, mat2, true);
}
Matrix subtract(Matrix mat1, Matrix mat2)
{
    return sum_sub(mat1, mat2, false);
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

    mat3.rows = mat1.rows;
    mat3.columns = mat2.columns;
    return mat3;
}
Matrix transpose(Matrix mat)
{
    return mat;
}

Matrix get_matrix_from_stdin()
{
    short int rows, columns;

    cout << "rows: ";
    cin >> rows;

    cout << "columns: ";
    cin >> columns;

    Number table[5][5];

    for (short int y = 0; y < rows; y++)
        for (short int x = 0; x < columns; x++)
        {
            string str_num;
            cin >> str_num;

            table[y][x] = Number(str_num);
        }

    return Matrix(rows, columns, table);
}

void show_matrix_in_stdout(Matrix &m)
{
    cout << '[' << endl;

    for (short int y = 0; y < m.rows; y++)
    {
        for (short int x = 0; x < m.columns; x++)
        {
            if (x != 0)
                cout << "  ";

            cout << m.table[y][x].printable_string();
        }
        cout << endl;
    }

    cout << ']' << endl;
}