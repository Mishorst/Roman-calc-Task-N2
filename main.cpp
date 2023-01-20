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

// Function to evaluate an arithmetic expression containing Roman numerals and operators
string romanCalculator(string input, map<char, int> &roman) {
    
    stack<int> nums; // stack to store numbers
    stack<char> ops; // stack to store numbers
    
    // Iterate through each character in the input string
    for (int i = 0; i < input.size(); i++) {
        
        // If the current character is a Roman numeral
        if (roman.count(input[i])) {
            string temp = "";
            
            // while loop to find all consecutive Roman numerals
            while (i < input.size() && roman.count(input[i])) temp += input[i++];
            i--;
            
            // Check if temp is noman numerical
            if(!check_roman(temp)){
                cout << "Enter correct Roman numerical" << endl;
                break;
            } else {
               // Convert the Roman numeral substring to an integer and push it onto the nums stack
                nums.push(romanToInt(temp, roman)); 
            }
        }
        // If the current character is an operator
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            
            // While the ops stack is not empty and the top element is * or /
            while (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
                int num2 = nums.top(); nums.pop();
                int num1 = nums.top(); nums.pop();
                char op = ops.top(); ops.pop();
                
                // Perform the corresponding arithmetic operation
                if (op == '*') {
                    nums.push(num1 * num2);
                } else if ((op == '/') && (num2 != 0)) { 
                    nums.push(num1 / num2);
                }
            }
            
            // Push the current operator onto the ops stack
            ops.push(input[i]);
        }
        
        // If the current character is an open parenthesis
        else if (input[i] == '(') {
            ops.push(input[i]);
        } 
        
        // If the current character is a close parenthesis
        else if (input[i] == ')') {
            
            // While the top element of the ops stack is not an open parenthesis
            while (ops.top() != '(') {
                int num2 = nums.top(); nums.pop();
                int num1 = nums.top(); nums.pop();
                char op = ops.top(); ops.pop();
                
                // Perform the corresponding arithmetic operation
                if (op == '+') {
                    nums.push(num1 + num2);
                } else if (op == '-') {
                    nums.push(num1 - num2);
                } else if (op == '*') {
                    nums.push(num1 * num2);
                } else if ((op == '/') && (num2 != 0)) { 
                    nums.push(num1 / num2);
                }
            }
            
            // Pop the open parenthesis from the ops stack
            ops.pop();
        }
    }
    
    // While the ops stack is not empty
    while (!ops.empty()) {
        int num2 = nums.top(); nums.pop();
        int num1 = nums.top(); nums.pop();
        char op = ops.top(); ops.pop();
        
        // Perform the corresponding arithmetic operation
        if (op == '+') {
            nums.push(num1 + num2);
        } else if (op == '-') {
            nums.push(num1 - num2);
        } else if (op == '*') {
            nums.push(num1 * num2);
        } else if ((op == '/') && (num2 != 0)) { 
            nums.push(num1 / num2);
        }
    }
    
    // If the ops stack is empty and there is only one element in the nums stack
    if (ops.empty() && nums.size() == 1) {
        map<int, string> roman_map = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
        
        // Convert the final result to a Roman numeral and return it
        return intToRoman(nums.top(), roman_map);
    } else {
        
        // If there is no final result
        return "Invalid input";
    }
}

int main(){
  string input;
    map<char, int> roman = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    
    cout << "Enter a Roman arithmetic expression (without spacing): ";
    cin >> input;
    
    cout << "Roman value: " << romanCalculator(input, roman) << endl;

  return 0;
}