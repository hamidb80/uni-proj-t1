#include "../math/number.h"
#include "../math/functions.h"

bool are_approxiamtly_equal(Number n1, Number n2, Number error)
{
    return is_greater(error, abs(subtract(n1, n2)));
}