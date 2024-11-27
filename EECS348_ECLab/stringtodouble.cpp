/*
11/27/2024
Luke Reicherter
KU ID: 3135060
EECS 348: Extra Credit Lab
Lab Session: Thursday 11:00 AM
Description: This program will take an input string and convert it to a double if possible.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

double extractNumeric(const string& str) {
    //This function converts a string to a double if possible. If not, it returns -999999.99
    //All variables used in the calulation are declared below
    double left_value = 0.0;
    double multiplier_handle = 1.0;
    double right_value = 0.0;
    double fraction_handle = 0.1;
    int tracker = 1;
    int sign = 1;
    //The code first checks if a decimal is in the string
    if (str.find(".") != string::npos) {
        //If a decimal is located, it attempts to loop through the left of the decimal
        for (int i = (str.find(".") - 1); i >= 0; i--) {
            //It first checks if the character is a digit
            if (isdigit(str[i])) {
                //If so, the value is added to the left value variable
                left_value = left_value + ((str[i] - '0') * multiplier_handle);
                //The multiplier is increased by 10
                multiplier_handle *= 10;
            } 
            //It then checks if the index is 0 and the character is a minus sign
            else if (str[i] == '-' && i == 0) {
                //If so, the sign variable is set to -1
                sign = -1;
            }
            //It also checks if the char is a plus sign
            else if (str[i] == '+' && i == 0) {
                //If so, the plus is ignored
                continue;
            }
            //If a variable is found to be not a digit or sign, the else statement occurs
            else {
                //-999999.99 is returned to show invalid input
                return -999999.99;
            }
            
        }
        //The fractional section of the string is the calculated by looping to the right of the decimal
        for (int i = (str.find(".") + 1); i < str.length(); i++) {
            //It first checks if the character is digit
            if (isdigit(str[i])) {
                //If so, the value is added to the right value variable
                right_value = (right_value + ((str[i] - '0') * fraction_handle));
                //The fraction handle is divided by 10
                fraction_handle /= 10;
            }
            //The else statement occurs if the character is not a digit
            else {
                //-999999.99 is returned to show invalid input
                return -999999.99;
            }
        }
    }
    //This else statement occurs if the input string does not contain a decimal
    else {
        //The code below is the same as the left value calculator, but uses .length to determine the rightmost char index
        for (int i = (str.length() - 1); i >= 0; i--) {
            if (isdigit(str[i])) {
                left_value = right_value + ((str[i] - '0') * multiplier_handle);
                multiplier_handle *= 10;
            } 
            else if (str[i] == '-' && i == 0) {
                sign = -1;
            }
            else if (str[i] == '+' && i == 0) {
                continue;
            }
            else {
                return -999999.99;
            }
        }
    }
    //The return value is calculated by adding the left and right values, and multiplying by a sign 
    return (left_value + right_value) * sign;
}

int main() {
    //The main function is responsible for handling the user input and displaying the output

    //The input variable is created
    string input;
    //This while loop has no condition, and will loop until the break statement occurs
    //This will allow the user to input multiple times
    while (true) {
        //Asks the user for input
        cout << "Enter a string (or 'END' to quit): ";
        //Stores the input
        cin >> input;
        //Checks if the user wants to end the program
        if (input == "END") {
            //If so, breaks out of the while loop
            break;
        }
        //Creates the output variable and sets it equal to the return value of the extractNumeric function
        double number = extractNumeric(input);
        //Checks if the the extractNumeric detected error
        if (number != -999999.99) {
            //If not, output is displayed with the precision of the double set to 4
            cout << "The input is: " << fixed << setprecision(4)
                 << number << endl;
        //This else statement occurs if an error has occured in the extractNumeric function
        } else {
            //Outputs an error message
            cout << "The input is invalid." << endl;
        }
    }
    //Ends program
    return 0;
}