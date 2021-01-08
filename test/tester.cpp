#include <iostream>
#include <string>
#include "../utils/test.h"
#include "../math/number.h"
#include "../math/matrix.h"
#include "../math/algebra.h"

using namespace std;

void test_number()
{
    // greater test
    error_if_were_not_equal(
        "999 > 999",
        is_greater(Number("999"), Number("999")),
        false);

    error_if_were_not_equal(
        "999 > 991",
        is_greater(Number("999"), Number("991")),
        true);

    error_if_were_not_equal(
        "1000 > 999",
        is_greater(Number("1000"), Number("999")),
        true);

    error_if_were_not_equal(
        "991 > 99.3",
        is_greater(Number("991"), Number("99.3")),
        true);

    // are equal
    error_if_were_not_equal(
        "999 == 999",
        are_equal(Number("999"), Number("999")),
        true);

    error_if_were_not_equal(
        "999 == 1000",
        are_equal(Number("999"), Number("1000")),
        false);

    error_if_were_not_equal(
        "1000 == 999",
        are_equal(Number("1000"), Number("999")),
        false);

    error_if_were_not_equal(
        "991 == 99.3",
        are_equal(Number("1000"), Number("99.3")),
        false);

    error_if_were_not_equal(
        "2 == 2.0000",
        are_equal(Number("2"), Number("2.0000")),
        true);

    // summation test
    error_if_were_not_equal(
        "991 + 999 ",
        sum(Number("999"), Number("991")).printable_string(),
        "1990");

    error_if_were_not_equal(
        "991 + 00",
        sum(Number("999"), Number("0")).printable_string(),
        "999");

    error_if_were_not_equal(
        "999 + 999",
        sum(Number("999"), Number("999")).printable_string(),
        "1998");

    error_if_were_not_equal(
        "79.64 + 1.1",
        sum(Number("79.64"), Number("1.1")).printable_string(),
        "80.74");

    error_if_were_not_equal(
        "5.400 + 5.11",
        sum(Number("5.400"), Number("5.11")).printable_string(),
        "10.51");

    //"subtraction test"
    error_if_were_not_equal(
        "991 - 999",
        subtract(Number("991"), Number("999")).printable_string(),
        "-8");

    error_if_were_not_equal(
        "3.14-0.314",
        subtract(Number("3.14"), Number("0.314")).printable_string(),
        "2.826");

    error_if_were_not_equal(
        "999 - 991",
        subtract(Number("999"), Number("991")).printable_string(),
        "8");

    error_if_were_not_equal(
        "14.888 - 89.3",
        subtract(Number("14.888"), Number("89.3")).printable_string(),
        "-74.412");

    error_if_were_not_equal(
        "10 - 10",
        subtract(Number("10"), Number("10")).printable_string(),
        "0");

    error_if_were_not_equal(
        "1201 - 991",
        subtract(Number("1201"), Number("991")).printable_string(),
        "210");

    error_if_were_not_equal(
        "79.64 - 1.1",
        subtract(Number("79.64"), Number("1.1")).printable_string(),
        "78.54");

    //"multipicataton test"
    error_if_were_not_equal(
        "24 * 67",
        multiplicate(Number("24"), Number("67")).printable_string(),
        "1608");

    error_if_were_not_equal(
        "999 * 999",
        multiplicate(Number("999"), Number("999")).printable_string(),
        "998001");

    error_if_were_not_equal(
        "79.64 * 79.64",
        multiplicate(Number("79.64"), Number("79.64")).printable_string(),
        "6342.5296");

    error_if_were_not_equal(
        "1.1 * 1.1",
        multiplicate(Number("1.1"), Number("1.1")).printable_string(),
        "1.21");

    error_if_were_not_equal(
        "79.64 * 1.1",
        multiplicate(Number("79.64"), Number("1.1")).printable_string(),
        "87.604");

    error_if_were_not_equal(
        "79.64 * 1",
        multiplicate(Number("79.64"), Number("1")).printable_string(),
        "79.64");

    error_if_were_not_equal(
        "46.300 * 0",
        multiplicate(Number("46.300"), Number("0")).printable_string(),
        "0");

    error_if_were_not_equal(
        "46.300 * 00",
        multiplicate(Number("46.300"), Number("00")).printable_string(),
        "0");

    error_if_were_not_equal(
        "1 * 4.5",
        multiplicate(Number("1"), Number("4.5")).printable_string(),
        "4.5");

    // division test
    error_if_were_not_equal(
        "14/2",
        divide(Number("14"), Number("2")).printable_string(),
        "7");

    error_if_were_not_equal(
        "8/2",
        divide(Number("8"), Number("2")).printable_string(),
        "4");

    error_if_were_not_equal(
        "1864/2",
        divide(Number("1864"), Number("2")).printable_string(),
        "932");

    error_if_were_not_equal(
        "199/2",
        divide(Number("199"), Number("2")).printable_string(),
        "99.5");

    error_if_were_not_equal(
        "10/3",
        divide(Number("10"), Number("3")).printable_string(),
        "3.33333");

    error_if_were_not_equal(
        "3.14/0.314",
        divide(Number("3.14"), Number("0.314")).printable_string(),
        "10");

    error_if_were_not_equal(
        "2000/2",
        divide(Number("2000"), Number("2")).printable_string(),
        "1000");

    error_if_were_not_equal(
        "12/12",
        divide(Number("12"), Number("12")).printable_string(),
        "1");

    error_if_were_not_equal(
        "99980001/9999",
        divide(Number("99980001"), Number("9999")).printable_string(),
        "9999");

    error_if_were_not_equal(
        "749/7",
        divide(Number("749"), Number("7")).printable_string(),
        "107");

    error_if_were_not_equal(
        "0.445/5",
        divide(Number("0.445"), Number("5")).printable_string(),
        "0.089");

    error_if_were_not_equal(
        "0.455/0.5",
        divide(Number("0.455"), Number("0.5")).printable_string(),
        "0.91");

    
    error_if_were_not_equal(
        "0.3/5",
        divide(Number("0.3"), Number("5")).printable_string(),
        "0.06");

    // "Number functionality"

    Number num1("1");

    string old_num1 = num1.printable_string();
    num1.shift_digits_for(2);

    error_if_were_not_equal(
        old_num1 + " shift for 2 indexes",
        num1.printable_string(),
        "100");

    string new_num1 = num1.printable_string();
    num1.shift_digits_for(-2);

    error_if_were_not_equal(
        new_num1 + " shift for -2 indexes",
        num1.printable_string(),
        "1");
}
void test_algebra()
{
    error_if_were_not_equal(
        "5+3",
        get_answer("5+3").printable_string(),
        "8");

    error_if_were_not_equal(
        "5+0.3",
        get_answer("5.3").printable_string(),
        "5.3");

    error_if_were_not_equal(
        "3-5",
        get_answer("3-5").printable_string(),
        "-2");

    error_if_were_not_equal(
        "34*1-5*4+1",
        get_answer("34*1-5*4+1").printable_string(),
        "15");

    error_if_were_not_equal(
        "9^3-1",
        get_answer("9^3-1").printable_string(),
        "728");

    error_if_were_not_equal(
        "9^3--1",
        get_answer("9^3--1").printable_string(),
        "730");
}

void test_entire_app()
{
    cout << "--- Fails ---" << endl;

    test_number();
    test_algebra();

    cout << "--- APP TESTED ---" << endl;
}