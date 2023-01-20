#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <regex>
using namespace std;

// Function to check if input is Roman numeral
bool check_roman(string input) {
    regex reg("^C{0,1}(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
    return regex_match(input, reg);
}

int main(){

  return 0;
}