#include <string>
#include <cstdlib>
#include "number.h"

using namespace std;

// TODO: cache `int length` value

Number
    P("3.141592"),
    E("2.753248"),
    N_0("0"), N_1("1"), N_10("10");

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

DivRes::DivRes(Number _qoutient, Number _reminder)
{
    qoutient = _qoutient;
    reminder = _reminder;
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
Number divide(Number dividend, Number divisor)
{
    if (are_equal(divisor, N_0))
        throw "division by zero";

    bool result_sign = dividend.sign == divisor.sign;
    dividend.sign = divisor.sign = 1;

    // delta float point length
    long int dfl = ((long int)dividend.float_length()) - ((long int)divisor.float_length());
    dividend.float_point_i = divisor.float_point_i = MAX_DIGITS - 1;

    if (dfl > 0)
        divisor.shift_digits_for(dfl);
    else if (dfl < 0)
        dividend.shift_digits_for(-dfl);

    long int dividend_len = dividend.int_length(),
             divisor_len = divisor.int_length();

    Number remainder;
    string qoutient_strnum = "";
    short int digits_after_point = 0;
    long int last_cut_index = MAX_DIGITS - dividend_len,
             digits_to_cut = std::min(dividend_len, divisor_len);

    while (true)
    {
        if (last_cut_index + digits_to_cut > MAX_DIGITS)
        {
            if ((are_equal(remainder, N_0) && !is_greater(divisor, dividend)) || digits_after_point == FLOAT_CLEAR_AFTER)
                break;

            if (digits_after_point == 0)
                qoutient_strnum.append(".");

            dividend = multiplicate(dividend, N_10);
            last_cut_index -= 1;
            digits_after_point += 1;
        }

        Number splited_dividend = sum(split_digits(dividend, last_cut_index, last_cut_index + digits_to_cut), remainder);

        if (!is_greater(divisor, splited_dividend))
        {
            DivRes division = simple_divide(splited_dividend, divisor);
            qoutient_strnum.append(division.qoutient.printable_string());

            remainder = multiplicate(division.reminder, N_10);
            last_cut_index += digits_to_cut;
            digits_to_cut = 0;
        }
        else
            qoutient_strnum.append("0");

        digits_to_cut += 1;
    }

    Number res(qoutient_strnum);
    res.sign = result_sign;

    return res;
}
// 13/4 => 3, 12/4 => 3
DivRes simple_divide(Number dividend, Number divisor)
{
    Number qoutient = N_0;

    while (!is_greater(divisor, dividend))
    {
        dividend = subtract(dividend, divisor);
        qoutient = sum(qoutient, N_1);
    }

    return DivRes(qoutient, dividend);
}

// comparation
// -- checks which one is greater (only respect to the absolute value)
bool is_greater(Number n1, Number n2)
{
    unsigned int
        n1_len = n1.int_length(),
        n2_len = n2.int_length();

    if (n1_len > n2_len)
        return true;

    sync_float_points(n1, n2);

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
bool are_equal(Number n1, Number n2)
{
    unsigned int
        n1_len = n1.int_length(),
        n2_len = n2.int_length();

    if (n1_len != n2_len)
        return false;

    sync_float_points(n1, n2);

    n1_len += n1.float_length();
    n2_len += n2.float_length();

    if (n1_len == n2_len)
        for (unsigned int i = 0; i < n1_len; i++)
        {
            short int
                n1_digit = n1.digits[MAX_DIGITS - (n1_len) + i],
                n2_digit = n2.digits[MAX_DIGITS - (n2_len) + i];

            if (n1_digit != n2_digit)
                return false;
        }

    return true;
}

// other functionalities
void sync_float_points(Number &n1, Number &n2)
{
    // delta float length
    long int dfl = ((long int)n1.float_length()) - ((long int)n2.float_length());

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
Number split_digits(Number n1, long int from, long int to)
{
    string str_num = "";

    for (long int i = from; i < to; i++)
        str_num.append(to_string(n1.digits[i]));

    return Number(str_num);
}