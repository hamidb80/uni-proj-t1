#pragma once
#include <string>
#include "../math/number.h"
#include "../math/matrix.h"

using namespace std;

void error_if_were_not_equal(string, bool, bool);
void error_if_were_not_equal(string, string, string);
void error_if_were_not_equal(string, Number, string);
void error_if_were_not_equal(string, Number, Number);
void error_if_were_not_equal(string, Matrix, Matrix);