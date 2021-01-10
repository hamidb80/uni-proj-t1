#include <iostream>
#include <string>
#include "../utils/test.h"
#include "../utils/number.h"
#include "../math/number.h"
#include "../math/functions.h"
#include "../math/matrix.h"
#include "../math/algebra.h"

using namespace std;

void test_number()
{
    { // greater test
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
    }
    { // are equal
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
    }
    { // summation test
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

        error_if_were_not_equal(
            "5 + -1",
            sum(Number("5"), Number("-1")).printable_string(),
            "4");

        error_if_were_not_equal(
            "-5 + -1",
            sum(Number("-5"), Number("-1")).printable_string(),
            "-6");

        error_if_were_not_equal(
            "-5 + 1",
            sum(Number("-5"), Number("1")).printable_string(),
            "-4");
    }
    { // subtraction test
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

        error_if_were_not_equal(
            "5 - -1",
            subtract(Number("5"), Number("-1")).printable_string(),
            "6");

        error_if_were_not_equal(
            "-5 - -1",
            subtract(Number("-5"), Number("-1")).printable_string(),
            "-4");

        error_if_were_not_equal(
            "-5 - 1",
            subtract(Number("-5"), Number("1")).printable_string(),
            "-6");
    }
    { // multipicataton test
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

        error_if_were_not_equal(
            "17 * 0.1",
            multiplicate(Number("17"), Number("0.1")).printable_string(),
            "1.7");
    }
    { // division test
        error_if_were_not_equal(
            "14/2",
            divide(Number("14"), Number("2")).printable_string(),
            "7");

        error_if_were_not_equal(
            "14/10",
            divide(Number("14"), Number("10")).printable_string(),
            "1.4");

        error_if_were_not_equal(
            "15/100",
            divide(Number("15"), Number("100")).printable_string(),
            "0.15");

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

        error_if_were_not_equal(
            "11/7",
            divide(Number("11"), Number("7")).printable_string(),
            "1.57142");

        error_if_were_not_equal(
            "7/11",
            divide(Number("7"), Number("11")).printable_string(),
            "0.63636");

        error_if_were_not_equal(
            "10/3",
            divide(Number("10"), Number("3")).printable_string(),
            "3.33333");

        error_if_were_not_equal(
            "10/3",
            divide(Number("10"), Number("3"), true).printable_string(),
            "3");

        error_if_were_not_equal(
            "2/3",
            divide(Number("2"), Number("3"), true).printable_string(),
            "0");
    }
    { // Number functionality

        Number num("45");

        string old_num = num.printable_string();
        num.shift_digits_for(2);

        error_if_were_not_equal(
            old_num + " shift for 2 indexes",
            num.printable_string(),
            "4500");

        string new_num = num.printable_string();
        num.shift_digits_for(-2);

        error_if_were_not_equal(
            new_num + " shift for -2 indexes",
            num.printable_string(),
            "45");
    }
}
void test_matrix() {}
void test_functions()
{
    { // power
        error_if_were_not_equal(
            "8^5",
            pow(Number("8"), Number("5")).printable_string(),
            "32768");

        error_if_were_not_equal(
            "(-2)^5",
            pow(Number("-2"), Number("5")).printable_string(),
            "-32");
    }
    { // fact
        error_if_were_not_equal(
            "8!",
            fact(Number("8")).printable_string(),
            "40320");
    }
    { // floor
        error_if_were_not_equal(
            "floor -8",
            abs(Number("-8")).printable_string(),
            "8");

        error_if_were_not_equal(
            "floor 8",
            abs(Number("8")).printable_string(),
            "8");

        error_if_were_not_equal(
            "floor 8.5",
            floor(Number("8.5")).printable_string(),
            "8");

        error_if_were_not_equal(
            "floor 8",
            floor(Number("8")).printable_string(),
            "8");

        error_if_were_not_equal(
            "floor -8.5",
            floor(Number("-8.5")).printable_string(),
            "-9");
    }
    { // ceil
        error_if_were_not_equal(
            "ceil -9",
            floor(Number("-9")).printable_string(),
            "-9");

        error_if_were_not_equal(
            "ceil 8.5",
            ceil(Number("8.5")).printable_string(),
            "9");

        error_if_were_not_equal(
            "ceil 8",
            ceil(Number("8")).printable_string(),
            "8");

        error_if_were_not_equal(
            "ceil -8.5",
            ceil(Number("-8.5")).printable_string(),
            "-8");

        error_if_were_not_equal(
            "ceil -9",
            ceil(Number("-9")).printable_string(),
            "-9");
    }
    { // mod
        error_if_were_not_equal(
            "10 mod 3",
            mod(Number("10"), Number("3")).printable_string(),
            "1");

        error_if_were_not_equal(
            "2 mod 3",
            mod(Number("2"), Number("3")).printable_string(),
            "2");

        error_if_were_not_equal(
            "999999999999999999 mod 2",
            mod(Number("999999999999999999"), Number("2")).printable_string(),
            "1");

        error_if_were_not_equal(
            "26 mod 26",
            mod(Number("26"), Number("2")).printable_string(),
            "0");

        error_if_were_not_equal(
            "3.13 mod 1",
            mod(Number("3.13"), Number("1")).printable_string(),
            "0.13");

        error_if_were_not_equal(
            "3.14 mod 3.141592",
            mod(Number("3.14"), Number("3.141592")).printable_string(),
            "3.14");

        error_if_were_not_equal(
            "31.45 mod 2.5",
            mod(Number("31.45"), Number("2.5")).printable_string(),
            "1.45");

        error_if_were_not_equal(
            "31.4 mod 3.14",
            mod(Number("31.4"), Number("3.14")).printable_string(),
            "0");

        error_if_were_not_equal(
            "4.71 mod 3.14",
            mod(Number("4.71"), Number("3.14")).printable_string(),
            "1.57");

        error_if_were_not_equal(
            "10 mod 0.3",
            mod(Number("10"), Number("0.3")).printable_string(),
            "0.1");
    }
    { // sin
        error_if_were_not_equal(
            "sin(1.57)",
            sin(Number("1.57")).printable_string(),
            "1");

        error_if_were_not_equal(
            "sin(0.785)",
            sin(Number("0.785")).printable_string(),
            "0.7");

        error_if_were_not_equal(
            "sin(2.355)",
            sin(Number("2.355")).printable_string(),
            "0.7");

        error_if_were_not_equal(
            "sin(3.14)",
            sin(Number("3.14")).printable_string(),
            "0");

        error_if_were_not_equal(
            "sin(314)",
            sin(Number("314")).printable_string(),
            "0");

        error_if_were_not_equal(
            "sin(4.71)",
            sin(Number("4.71")).printable_string(),
            "-1");
    }
    { // cos

        error_if_were_not_equal(
            "cos(1.57)",
            cos(Number("1.57")).printable_string(),
            "0");

        error_if_were_not_equal(
            "cos(0.785)",
            cos(Number("0.785")).printable_string(),
            "0.7");

        error_if_were_not_equal(
            "cos(2.355)",
            cos(Number("2.355")).printable_string(),
            "-0.7");

        error_if_were_not_equal(
            "cos(3.14)",
            cos(Number("3.14")).printable_string(),
            "-1");

        error_if_were_not_equal(
            "cos(0)",
            cos(Number("0")).printable_string(),
            "1");

        error_if_were_not_equal(
            "cos(4.71)",
            cos(Number("4.71")).printable_string(),
            "0");
    }
}
void test_algebra()
{
    { // get_next_algebra

        error_if_were_not_equal(
            "next algebra of (654)",
            get_next_algebra("(654)", 5).value,
            "654");

        error_if_were_not_equal(
            "next algebra of (6*1^(43+4)-12), 5",
            get_next_algebra("(6*1^(43+4)-12)", 5).value,
            "6*1^(43+4)-12");

        error_if_were_not_equal(
            "next algebra of 6*1^(43+4)-12, 2",
            get_next_algebra("6*1^(43+4)-12", 2).value,
            "6");

        error_if_were_not_equal(
            "next algebra of 6*1^(43+4)-12, 5",
            get_next_algebra("6*1^(43+4)-12", 5).value,
            "6");

        error_if_were_not_equal(
            "next algebra of 6*1^(43+4)-12, 1",
            get_next_algebra("6*1^(43+4)-12", 1).value,
            "6*1^(43+4)");
    }
    { // get_answer
        error_if_were_not_equal(
            "5+3",
            get_answer("5+3").printable_string(),
            "8");

        error_if_were_not_equal(
            "5+0.3",
            get_answer("5+0.3").printable_string(),
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
            "6*(2+2)+1",
            get_answer("6*(2+2)+1").printable_string(),
            "25");

        error_if_were_not_equal(
            "1/2*2^3-5",
            get_answer("1/2*2^3-5").printable_string(),
            "-1");

        error_if_were_not_equal(
            "1/2*2^(1+1)-5",
            get_answer("1/2*2^(1+1)-5").printable_string(),
            "-3");

        error_if_were_not_equal(
            "9^3--1",
            get_answer("9^3--1").printable_string(),
            "730");

        error_if_were_not_equal(
            "5*3+(7*2+3*(3.5*9)-(-3))/7",
            get_answer("5*3+(7*2+3*(3.5*9)-(-3))/7").printable_string(),
            "30.92857");

        error_if_were_not_equal(
            "(2)+(1)*(5)*(-3)-(-(-4))",
            get_answer("(2)+(1)*(5)*(-3)-(-(-4))").printable_string(),
            "-17");

        error_if_were_not_equal(
            "((2)+(1))/(5)-((-3)-(-(-4)))",
            get_answer("((2)+(1))/(5)-((-3)-(-(-4)))").printable_string(),
            "7.6");

        // function call
        error_if_were_not_equal(
            "1+sin(1.57)*3^2",
            get_answer("1+sin(1.57)*3^2").printable_string(),
            "10");

        error_if_were_not_equal(
            "fact(5)/5+1",
            get_answer("(fact(5)/5+1)^2").printable_string(),
            "625");

        // nested function call
        error_if_were_not_equal(
            "fact(fact(abs(-3)-1))",
            get_answer("fact(fact(abs(-3)-1))").printable_string(),
            "2");
    }
}
void test_entire_app()
{
    cout << "--- Fails ---" << endl;

    test_matrix();
    test_number();
    test_functions();
    test_algebra();

    cout << "--- APP TESTED ---" << endl;
}