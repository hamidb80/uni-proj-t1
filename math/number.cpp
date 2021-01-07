#include <string>
#include <cstdlib>
#include "number.h"

using namespace std;

// constructors
Number::Number()
{
    float_point_i = MAX_DIGITS - 1;
    base = "10";
    sign = 1;
}
Number::Number(string str_num, string _base)
{
    base = _base;

    // -923 => sign:0, str_num: 923
    sign = str_num[0] != '-';
    if (sign == 0)
        str_num = str_num.substr(1);

    long int fpi = str_num.find('.');
    if (fpi == -1)
        float_point_i = MAX_DIGITS - 1;
    else
    {
        float_point_i = (MAX_DIGITS - ((str_num.length() - (1 + fpi)) + 1));
        str_num.replace(fpi, 1, "");
    }

    for (unsigned int i = 0; i < str_num.length(); i++)
        digits[MAX_DIGITS - (i + 1)] = (int)str_num[str_num.length() - (1 + i)] - 48;
}

// methods
unsigned int Number::int_length()
{
    unsigned int first_non_zero_number_i = float_point_i;
    for (unsigned int i = 0; i < MAX_DIGITS && i <= float_point_i; i++)
        if (digits[i] != 0)
        {
            first_non_zero_number_i = i;
            break;
        }

    return (MAX_DIGITS - first_non_zero_number_i) - float_length();
}
unsigned int Number::float_length()
{
    return MAX_DIGITS - (float_point_i + 1);
}
void Number::shift_digits_for(int shift_number)
{
    unsigned int len = int_length() + float_length();

    if (shift_number > 0)
    {
        // shift indexes backward for `shift_number`
        for (unsigned int i = len; i > 0; i--)
            digits[MAX_DIGITS - (i + shift_number)] = digits[MAX_DIGITS - (i)];

        // clear the rest
        for (unsigned int i = 0; i < shift_number; i++)
            digits[MAX_DIGITS - (i + 1)] = 0;
    }

    else if (shift_number < 0)
    {
        // shift indexes forward `shift_number`
        for (unsigned int i = 0; i < len; i++)
            digits[MAX_DIGITS - (i + 1)] = digits[MAX_DIGITS - (-shift_number + i + 1)];
    }
}
void Number::clean_float()
{
    int should_shift_backward = 0;
    for (unsigned int i = MAX_DIGITS - 1; i > float_point_i; i--)
    {
        if (digits[i] == 0)
            should_shift_backward++;
        else
            break;
    }

    shift_digits_for(-should_shift_backward);
    float_point_i += should_shift_backward;
}
string Number::printable_string()
{
    clean_float();

    string str_num = "";
    unsigned int len = int_length() + float_length();

    for (unsigned int i = 0; i < len; i++)
        str_num = to_string(digits[MAX_DIGITS - (i + 1)]) + str_num;

    if (float_point_i != MAX_DIGITS - 1)
    {
        unsigned int offset_from_end = MAX_DIGITS - (1 + float_point_i);
        str_num.insert(str_num.length() - (offset_from_end), ".");
    }

    return (sign == 0 ? "-" : "") + str_num;
}

// operations
Number sum(Number n1, Number n2)
{
    sync_float_points(n1, n2);

    // do subtraction if their signes arn't the same
    if (n1.sign != n2.sign)
        return subtract(n1, n2);

    Number n3;
    n3.sign = n1.sign;

    short int carry = 0;
    for (unsigned int i = 0; i < MAX_DIGITS; i++)
    {
        short int temp_sum = n1.digits[MAX_DIGITS - (i + 1)] + n2.digits[MAX_DIGITS - (i + 1)] + carry;
        n3.digits[MAX_DIGITS - (i + 1)] = temp_sum % 10;
        carry = temp_sum / 10;
    }

    n3.float_point_i = n2.float_point_i;
    return n3;
}
Number subtract(Number n1, Number n2)
{
    sync_float_points(n1, n2);

    // do summation if their signes aren't the same
    if (n1.sign != n2.sign)
    {
        n2.sign = !n2.sign;
        return sum(n1, n2);
    }

    Number n3;
    //n1 always contains the larger number
    if (is_greater(n2, n1))
    {
        swap(n1, n2);
        n3.sign = 0;
    }

    short int carry = 0;
    for (unsigned int i = 0; i < MAX_DIGITS; i++)
    {
        short int temp_minus = n1.digits[MAX_DIGITS - (i + 1)] - n2.digits[MAX_DIGITS - (i + 1)] + carry;

        carry = 0;
        while (temp_minus < 0)
        {
            temp_minus += 10;
            carry -= 1;
        }

        n3.digits[MAX_DIGITS - (i + 1)] = temp_minus;
    }

    n3.float_point_i = n1.float_point_i;
    return n3;
}
Number multiplicate(Number n1, Number n2)
{
    Number n3;

    unsigned int
        n1_len = n1.int_length() + n1.float_length(),
        n2_len = n2.int_length() + n2.float_length();

    // multipicate & put summation in result index [digits can be more than 9]
    for (unsigned int i = 0; i < n1_len; i++)
    {
        unsigned int n1_digit = n1.digits[MAX_DIGITS - (i + 1)];
        if (n1_digit == 0)
            continue;

        for (unsigned int j = 0; j < n2_len; j++)
        {
            unsigned int n2_digit = n2.digits[MAX_DIGITS - (j + 1)];
            if (n2_digit == 0)
                continue;

            n3.digits[MAX_DIGITS - (i + j + 1)] += n1_digit * n2_digit;
        }
    }

    // collect & correct indexes which contain digits greater than 9
    unsigned int n3_len = n3.int_length() + n3.float_length();
    unsigned int carry = 0;
    for (unsigned int i = 0; (i < n3_len) || (carry != 0); i++)
    {
        unsigned int digit = n3.digits[MAX_DIGITS - (i + 1)] + carry;
        if (digit >= 10)
        {
            carry = digit / 10;
            digit = digit % 10;
        }
        else
            carry = 0;

        n3.digits[MAX_DIGITS - (i + 1)] = digit;
    }

    n3.float_point_i = MAX_DIGITS - (n1.float_length() + n2.float_length() + 1);
    return n3;
}
Number divide(Number n1, Number n2)
{
    Number remain, n3;
    return n1;
}

// comparation
// -- checks which one is greater without respect to sign (absolute value)
bool is_greater(Number &n1, Number &n2)
{
    // FIXME:
    // sync_float_points(n1, n2);

    unsigned int
        n1_len = n1.int_length(),
        n2_len = n2.int_length();

    if (n1_len > n2_len)
        return true;

    n1_len += n1.float_length();
    n2_len += n2.float_length();

    if (n1_len == n2_len)
        for (unsigned int i = 0; i < n1_len; i++)
        {
            short int
                n1_digit = n1.digits[MAX_DIGITS - (n1_len) + i],
                n2_digit = n2.digits[MAX_DIGITS - (n2_len) + i];

            if (n1_digit != n2_digit)
                return n1_digit > n2_digit;
        }

    return false;
}

// other functionalities
void sync_float_points(Number &n1, Number &n2)
{
    // delta float length
    unsigned int dfl = n1.float_length() - n2.float_length();

    if (dfl > 0)
    {
        n2.shift_digits_for(dfl);
        n2.float_point_i -= dfl;
    }
    else if (dfl < 0)
    {
        n1.shift_digits_for(-dfl);
        n1.float_point_i -= -dfl;
    }
}