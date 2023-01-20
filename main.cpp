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

// Function to convert a Roman numeral string to an integer
int romanToInt(string s, map<char, int> &roman) {
    int result = 0;
    for (int i = 0; i < s.size(); i++) {
        
        // Add the value of the current Roman numeral
        result += roman[s[i]];
        
        // Check if the current Roman numeral has a lower value than the previous one
        if (i > 0 && roman[s[i]] > roman[s[i - 1]])
        
            // Subtract the value of the previous Roman numeral twice as it has been added in the previous step
            result -= 2 * roman[s[i - 1]];
    }
    return result;
}

// Function to convert an integer to a Roman numeral string
string intToRoman(int num, map<int, string> &roman) {
    string result = "";
    
    // Iterate through the map in descending order
    for (auto it = roman.rbegin(); it != roman.rend(); it++) {
        
        // While the number is greater than or equal to the current value
        while (num >= it->first) {
            
            // Subtract the current value from the number
            num -= it->first;
            
            // Append the corresponding Roman numeral to the result string
            result += it->second;
        }
    }
    return result;
}

int main(){

  return 0;
}