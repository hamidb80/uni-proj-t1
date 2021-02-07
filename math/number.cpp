#include <string>
#include <vector>
#include <cstdlib>

#include "number.h"

using namespace std;

Number
    P("3.14159"),
    _P2("1.57079"),
    P2("6.28318"),
    E("2.71828"),

    N_0("0"),
    N_1("1"), _N_1("-1"),
    N_2("2"), N_10("10");

short int char2digit(char ch)
{
    return ch - '0';
}

// constructors
Number::Number()
{
    // default assignment to zero
    digits.push_back(0);
    float_point_i = 1;
    sign = 1;
}
Number::Number(string str_num)
{
    sign = str_num[0] != '-';

    if (sign == 0)
        str_num = str_num.substr(1);

    // set the float point
    long int fpi = str_num.find('.');
    if (fpi == -1)
        float_point_i = str_num.length();
    else
    {
        float_point_i = fpi;
        str_num.replace(fpi, 1, "");
    }

    // add numbers from string to digits vector
    for (long int i = 0; i < str_num.length(); i++)
        digits.push_back(char2digit(str_num[i]));
}

// methods
long int Number::float_length()
{
    return (long int)digits.size() - (long int)float_point_i;
}
long int Number::int_length()
{
    return (long int)digits.size() - float_length();
}

// shift number backward/forward
void Number::shift_digits_for(long int shift_number)
{
    if (shift_number > 0)
        digits.insert(digits.end(), shift_number, 0);
    else
        digits.erase(digits.end() + shift_number, digits.end());
}
void Number::clean()
{
    // float section
    long int floats_to_remove = 0;
    for (long int i = digits.size() - 1; i >= float_point_i; i--)
    {
        if (digits[i] == 0)
            floats_to_remove++;
        else
            break;
    }
    digits.erase(digits.end() - floats_to_remove, digits.end());

    // int section
    int digits_to_remove = 0;
    for (long int i = 0; i < float_point_i - 1; i++)
    {
        if (digits[i] == 0)
            digits_to_remove++;
        else
            break;
    }
    digits.erase(digits.begin(), digits.begin() + digits_to_remove);
    float_point_i -= digits_to_remove;

    // -0 => 0
    if (digits.size() == 1 && digits[0] == 0)
        sign = true;
}
void Number::remove_float_after(short int num)
{
    if (float_length() > num)
        shift_digits_for(num - float_length());
}

string Number::printable_string()
{
    remove_float_after();
    clean();

    return raw_string();
}
string Number::raw_string()
{
    string str_num = "";
    for (unsigned i = 0; i < digits.size(); i++)
        str_num.append(to_string(digits[i]));

    if (float_point_i < digits.size())
        str_num.insert(float_point_i, ".");

    return (sign == 0 ? "-" : "") + str_num;
}

// operations
Number sum(Number n1, Number n2)
{
    // do subtraction if their signes arn't the same
    if (n1.sign != n2.sign)
    {
        if (n1.sign == false)
        {
            n1.sign = true;
            return subtract(n2, n1);
        }
        else
        {
            n2.sign = true;
            return subtract(n1, n2);
        }
    }

    Number res;
    sync_num(n1, n2);
    sync_num(n1, res);

    // add another zero digit for result of the summation (because that can overflow like 9+9 = 18)
    res.digits.insert(res.digits.begin(), 1, 0);
    res.float_point_i++;

    long int num_len = n1.digits.size();
    long int carry = 0;
    for (long int i = num_len - 1; i >= 0; i--)
    {
        long int temp_sum = n1.digits[i] + n2.digits[i] + carry;
        res.digits[i + 1] = temp_sum % 10;
        carry = temp_sum / 10;
    }

    res.digits[0] = carry;
    res.sign = n1.sign;
    return res;
}
Number subtract(Number n1, Number n2)
{
    // do summation if their signes aren't the same
    if (n2.sign == false)
    {
        n2.sign = true;
        return sum(n1, n2);
    }
    else if (n1.sign == false)
    {
        n2.sign = false;
        return sum(n1, n2);
    }

    Number res;
    sync_num(n1, n2);
    sync_num(res, n2);

    // n1 always contains the larger number
    if (is_greater(n2, n1))
    {
        swap(n1, n2);
        res.sign = false;
    }

    short int carry = 0;
    for (int i = n1.digits.size() - 1; i >= 0; i--)
    {
        short int temp_minus = n1.digits[i] - n2.digits[i] + carry;
        carry = 0;
        while (temp_minus < 0)
        {
            temp_minus += 10;
            carry -= 1;
        }
        res.digits[i] = temp_minus;
    }

    res.float_point_i = n1.float_point_i;
    return res;
}
Number multiplicate(Number n1, Number n2)
{
    unsigned
        n1_len = n1.digits.size(),
        n2_len = n2.digits.size();

    Number n3;
    n3.digits.insert(n3.digits.begin(), n1_len + n2_len - 1, 0);

    // multipicate & put summation in result index [digits can be more than 9]
    for (int i = n1_len - 1; i >= 0; i--)
        for (int j = n2_len - 1; j >= 0; j--)
            n3.digits[i + j + 1] += n1.digits[i] * n2.digits[j];

    // collect & correct indexes which contain digits greater than 9
    unsigned n3_len = n3.digits.size(),
             carry = 0;

    for (int i = n3_len - 1; i >= 0; i--)
    {
        unsigned temp = n3.digits[i] + carry;
        carry = temp / 10;
        n3.digits[i] = temp % 10;
    }

    n3.float_point_i = n3_len - (n1.float_length() + n2.float_length());
    n3.sign = (n1.sign == n2.sign);
    return n3;
}
Number divide(Number dividend, Number divisor, bool is_int_div)
{
    if (are_equal(divisor, N_0))
        throw string("division by zero");

    if (are_equal(dividend, N_0))
        return N_0;

    // predict sign of result
    bool result_sign = (dividend.sign == divisor.sign);
    dividend.sign = divisor.sign = 1; // posivite both for multipication

    // remove float points: 12, 0.3 => 120, 3
    sync_float_points(dividend, divisor);
    dividend.float_point_i = dividend.digits.size();
    divisor.float_point_i = divisor.digits.size();
    dividend.clean();
    divisor.clean();

    // prepare for operation
    Number remainder;
    string qoutient_strnum = "";
    long int dividend_len = dividend.digits.size(),
             divisor_len = divisor.digits.size(),
             digits_after_point = 0,
             last_cut_index = 0,
             digits_to_cut = min(dividend_len, divisor_len);

    while (true)
    {
        // if digits that we want to split from dividend was bigger than dividend
        if ((last_cut_index + digits_to_cut) > dividend_len)
        {
            // if reminder != 0 and
            if ((are_equal(remainder, N_0) && !is_greater(divisor, dividend)) ||
                digits_after_point >= KEEP_FLOAT_BEFORE || is_int_div)
                break;

            if (digits_after_point == 0)
                qoutient_strnum.append(".");

            dividend = multiplicate(dividend, N_10);
            last_cut_index += 1;
            digits_after_point += 1;
        }

        Number splited_dividend = sum(
            split_digits(dividend, last_cut_index, last_cut_index + digits_to_cut), remainder);

        if (is_smaller_equal(divisor, splited_dividend))
        {
            DivRes division = simple_divide(splited_dividend, divisor);
            qoutient_strnum.append(division.qoutient.printable_string());

            remainder = division.reminder;
            last_cut_index += digits_to_cut;
            digits_to_cut = 0;
        }
        else
            qoutient_strnum.append("0");

        remainder = multiplicate(remainder, N_10);
        digits_to_cut += 1;
    }

    Number res(qoutient_strnum);
    res.sign = result_sign;
    return res;
}
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

// comparations
bool are_equal(Number n1, Number n2)
{
    n1.clean();
    n2.clean();

    if (n1.int_length() != n2.int_length() || n1.sign != n2.sign)
        return false;

    sync_num(n1, n2);

    for (unsigned i = 0; i < n1.digits.size(); i++)
        if (n1.digits[i] != n2.digits[i])
            return false;

    return true;
}
bool is_greater(Number n1, Number n2)
{
    if (n1.sign != n2.sign)
        return n1.sign;

    n1.clean();
    n2.clean();

    if (n1.int_length() != n2.int_length())
    {
        // if they were positive
        if (n1.sign)
            return n1.int_length() > n2.int_length();
        else
            return n2.int_length() > n1.int_length();
    }

    sync_num(n1, n2);

    for (unsigned i = 0; i < n1.digits.size(); i++)
    {
        short int
            n1_digit = n1.digits[i],
            n2_digit = n2.digits[i];

        if (n1_digit != n2_digit)
        {
            // if they were positive
            if (n1.sign)
                return n1_digit > n2_digit;
            else
                return n1_digit < n2_digit;
        }
    }

    return false;
}
bool is_smaller_equal(Number n1, Number n2)
{
    return !is_greater(n1, n2);
}
bool is_smaller(Number n1, Number n2)
{
    return is_greater(n2, n1);
}
bool is_greater_equal(Number n1, Number n2)
{
    return is_smaller_equal(n2, n1);
}

// other functionalities
void sync_float_points(Number &n1, Number &n2)
{
    // delta float length
    long int dfl = n1.float_length() - n2.float_length();

    if (dfl > 0)
        n2.shift_digits_for(dfl);
    else if (dfl < 0)
        n1.shift_digits_for(-dfl);
}
void sync_int(Number &n1, Number &n2)
{
    // delta int length
    long int dil = n1.int_length() - n2.int_length();

    if (dil > 0)
    {
        n2.digits.insert(n2.digits.begin(), dil, 0);
        n2.float_point_i += dil;
    }
    else if (dil < 0)
    {
        n1.digits.insert(n1.digits.begin(), -dil, 0);
        n1.float_point_i += -dil;
    }
}
void sync_num(Number &n1, Number &n2)
{
    sync_float_points(n1, n2);
    sync_int(n1, n2);
}

Number split_digits(Number n1, long int from, long int to)
{
    string str_num = "";

    for (long int i = from; i < to; i++)
        str_num.append(to_string(n1.digits[i]));

    return Number(str_num);
}