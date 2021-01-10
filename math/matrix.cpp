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
Matrix sum_sub(Matrix m1, Matrix m2, bool is_sum)
{
    Matrix mat3;

    // proc mat3
    for (int y = 0; y < m1.rows; y++)
        for (int x = 0; x < m1.columns; x++)
        {
            if (is_sum)
                mat3.table[y][x] = sum(m1.table[y][x], m2.table[y][x]);
            else
                mat3.table[y][x] = subtract(m1.table[y][x], m2.table[y][x]);
        }

    mat3.columns = m1.columns;
    mat3.rows = m1.rows;
    return mat3;
}
Matrix sum(Matrix m1, Matrix m2)
{
    return sum_sub(m1, m2, true);
}
Matrix subtract(Matrix m1, Matrix m2)
{
    return sum_sub(m1, m2, false);
}
Matrix multiplicate(Matrix m1, Matrix m2)
{
    Matrix mat3;

    // proc mat3
    for (int y = 0; y < m1.rows; y++)
    {
        for (int x = 0; x < m2.columns; x++)
        {
            Number _sum("0", "10");

            for (int c = 0; c < m1.columns; c++)
                _sum = sum(_sum, multiplicate(
                                     m1.table[y][c], m2.table[c][x]));

            mat3.table[y][x] = _sum;
        }
    }

    mat3.rows = m1.rows;
    mat3.columns = m2.columns;
    return mat3;
}
Matrix transpose(Matrix m)
{
    Matrix res;
    res.columns = m.rows;
    res.rows = m.columns;

    for (short int y = 0; y < m.rows; y++)
        for (short int x = 0; x < m.columns; x++)
            res.table[x][y] = m.table[y][x];

    return res;
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