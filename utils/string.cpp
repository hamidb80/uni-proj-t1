#include <string>
using namespace std;

string remove_spaces(string str)
{
    string result = "";

    for (unsigned i = 0; i < str.length(); i++)
        if (str[i] != ' ')
            result += str[i];

    return result;
}