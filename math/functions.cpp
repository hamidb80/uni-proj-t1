#include "number.h"
#include "functions.h"

extern Number P, P2, E, N_0, N_1, _N_1, N_2, N_10;
const short int
    max_hyperbolic_s = 5,
    max_triangle_s = 5;

Number pow(Number base, Number num)
{
    num.clean_float();
    if (num.float_length() != 0)
        throw "power function: number must be integer";

    Number res = N_1, i = N_1;

    for (; is_smaller_equal(i, num); i = sum(i, N_1))
        res = multiplicate(res, base);

    return res;
}
Number fact(Number num)
{
    num.clean_float();
    if (num.float_length() != 0)
        throw "fact function: value must be an integer";

    Number res = N_1, i = num;

    for (; is_greater(i, N_0); i = subtract(i, N_1))
        res = multiplicate(res, i);

    return res;
}
Number abs(Number num)
{
    if (num.sign == 0)
        num.sign = 1;

    return num;
}
Number floor(Number num)
{
    // clear digits after float point
    if (num.float_length() != 0 && num.sign == false)
        num = subtract(num, N_1);

    // FIXME: becuase float_length() return type is unsigned integer, this probably overflows
    num.shift_digits_for(-num.float_length());
    num.float_point_i = MAX_DIGITS - 1;

    return num;
}
Number ceil(Number num)
{
    // clear digits after float point
    if (num.float_length() != 0 && num.sign == true)
        num = sum(num, N_1);

    // FIXME: becuase float_length() return type is unsigned integer, this probably overflows
    num.shift_digits_for(-num.float_length());
    num.float_point_i = MAX_DIGITS - 1;

    return num;
}
Number mod(Number dividend, Number divisor)
{
    return subtract(dividend, multiplicate(
                                  divide(dividend, divisor, true),
                                  divisor));
}
Number ln(Number n)
{
    Number _sum, top = divide(subtract(n, N_1), sum(n, N_1));

    // TODO increase max
    for (int i = 1; i < 20; i += 2)
    {
        Number inum(to_string(i));
        _sum = sum(_sum, divide(pow(top, inum), inum));
    }

    return multiplicate(N_2, _sum);
}
Number log(Number base, Number num)
{
    return divide(ln(num), ln(base));
}
Number radical(Number base, Number num)
{
    return base;
}

Number sin(Number rad)
{
    rad = mod(rad, P2);
    bool sign = !is_greater(rad, P);
    rad = mod(rad, P);

    Number _sum;
    for (short int i = 0; i < max_triangle_s; i++)
    {
        Number
            inum(to_string(i)),
            n2_1 = sum(multiplicate(N_2, inum), N_1);

        _sum = sum(_sum,
                   multiplicate(
                       divide(
                           pow(_N_1, inum), fact(n2_1)),
                       pow(rad, n2_1)));
    }

    _sum.sign = sign;
    if (is_greater(abs(_sum), N_1))
    {
        bool sign = _sum.sign;
        _sum = N_1;
        _sum.sign = sign;
    }

    return _sum;
}
Number cos(Number rad)
{
    rad = mod(rad, P2);
    // TODO:
    // bool sign = !is_greater(rad, P);
    // rad = mod(rad, P);

    Number _sum;
    for (short int i = 0; i < max_triangle_s; i++)
    {
        Number inum(to_string(i)),
            n2 = multiplicate(N_2, inum);

        _sum = sum(_sum,
                   multiplicate(
                       divide(
                           pow(_N_1, inum), fact(n2)),
                       pow(rad, n2)));
    }

    if (is_greater(abs(_sum), N_1))
    {
        bool sign = _sum.sign;
        _sum = N_1;
        _sum.sign = sign;
    }

    return _sum;
}
Number tan(Number rad)
{
    return divide(sin(rad), cos(rad));
}
Number cot(Number rad)
{
    return divide(cos(rad), sin(rad));
}
Number sec(Number rad)
{
    return divide(N_1, cos(rad));
}
Number csc(Number rad)
{
    return divide(N_1, sin(rad));
}

Number sinh(Number x)
{
    Number _sum;

    for (int i = 0; i < max_hyperbolic_s; i++)
    {
        Number
            inum(to_string(i)),
            n_2_1 = sum(multiplicate(N_2, inum), N_1);

        _sum = sum(_sum, divide(
                             pow(x, n_2_1), fact(n_2_1)));
    }

    return _sum;
}
Number cosh(Number x)
{
    Number _sum;

    for (int i = 0; i < max_hyperbolic_s; i++)
    {
        Number
            inum(to_string(i)),
            n_2 = multiplicate(N_2, inum);

        _sum = sum(_sum, divide(
                             pow(x, n_2), fact(n_2)));
    }

    return (is_greater(N_1, _sum) ? N_1 : _sum);
}
Number tanh(Number num)
{
    Number res = divide(sinh(num), cosh(num));

    if (is_greater(abs(res), N_1))
    {
        bool sign = res.sign;
        res = N_1;
        res.sign = sign;
    }

    return res;
}
Number coth(Number num)
{
    Number res = divide(cosh(num), sinh(num));

    if (is_greater(N_1, abs(res)))
    {
        bool sign = res.sign;
        res = N_1;
        res.sign = sign;
    }
    return res;
}