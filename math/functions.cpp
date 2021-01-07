#include "number.h"
#include "functions.h"

Number pow(Number base, Number num)
{
    // assert num be intgger
    // TODO: throw an error
    if (num.float_length() == 0)
        ;

    Number res = n1, i = n1;

    for (; !is_greater(i, num); i = sum(i, n1))
        res = multiplicate(res, base);

    return res;
}
Number fact(Number num)
{
    // assert num be intgger
    // TODO: throw an error
    if (num.float_length() == 0)
        ;

    Number res = n1, i = num;

    for (; is_greater(i, n0); i = subtract(i, n1))
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