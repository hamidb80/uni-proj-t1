#include <iostream>

#include "number.h"
#include "matrix.h"

using namespace std;

// constructors
Matrix::Matrix()
{
    rows = columns = 0;
}
Matrix::Matrix(int _rows, int _columns, Number _table[MAX_ROWS][MAX_COLUMNS])
{
    rows = _rows;
    columns = _columns;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
            table[y][x] = _table[y][x];
}

string Matrix::in_row_string()
{
    string res;
    for (int y = 0; y < rows; y++)
    {
        res += "[";
        for (int x = 0; x < columns; x++)
        {
            if (x != 0)
                res += ",";
            res += table[y][x].printable_string();
        }
        res += "]";
    }

    return res;
}

// operations
Matrix sum_sub(Matrix m1, Matrix m2, bool is_sum)
{
    Matrix mat3;

    if (m1.rows != m2.rows || m2.columns != m1.columns)
        throw string("rows & coloumn of matrixes must be the same");

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
    if (m1.columns != m2.rows)
        throw string("cannot multipicate matrixes with size " + to_string(m1.rows) + "x" + to_string(m1.columns) + " with " + to_string(m2.rows) + "x" + to_string(m2.columns));

    Matrix mat3;

    // proc mat3
    for (int y = 0; y < m1.rows; y++)
    {
        for (int x = 0; x < m2.columns; x++)
        {
            Number _sum("0");

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

// utilities
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