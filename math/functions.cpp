#include "number.h"
#include "functions.h"

extern Number P, E, N_0, N_1, N_10;

Number pow(Number base, Number num)
{
    num.clean_float();
    if (num.float_length() != 0)
        throw "power function: number must be integer";

    Number res = N_1, i = N_1;

    for (; !is_greater(i, num); i = sum(i, N_1))
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
// Number floor(Number num) {}
// Number ceil(Number num) {}

// Number ln(Number number) {}
// Number log(Number base, Number number) {}
// Number radical(Number base, Number num) {}

// Number sin(Number num) {}
// Number cos(Number num) {}
// Number tan(Number num) {}

// Number sinh(Number num) {}
// Number cosh(Number num) {}
// Number tanh(Number num) {}