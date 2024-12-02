#include <iostream>
#include <iomanip>
#include <string>
#include <set>

//to avoid repeating std::
using namespace std;

//extractNumeric function which checks the number entered in main function to see if it's valid, and generates an output for the end of the main function
double extractNumeric(const string& str){
    int i; //initializes the letter i as an integer variable used for counting in the for loop
    int numDecimals = 0; //counting variable for the number of decimals in the user-inputted string, we need to make sure that there are not more than decimals, because if so, the input is invalid
    bool numInSet = false; //boolean statement that checks to see if a character in the string is in the set of valid characters (numbers 0-9). This will be set by default to false.
    bool negativeNumber = false; //boolean statement that determines if the number entered is negative or positive. By deault we will set this to false, meaning the number is assumed positive since a positive number doesn't need a sign in front of it
    double decimal = 0.1; //double precision variable called decimal, which will be used to get the proper amount of decimal on the number inputted by a user. The output is expected to be 4 decimal places long assuming the inputted number is valid
    double output; //a variable with double precision uesd to store the value of the resulting string when transformed into a numeric value
    
    set<char> validNumbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //as explained in the numInSet comment, the only valid numbers are 0-9. So a character that isn't a number, a positive/negative sign, or decimal point in the string would be an invalid input

    if (str.length() > 20){ //quick check to see if the length of the string is greater than 20 characters long. As outlined in the first bullet-point of the input directions, a string has a max length of 20 for "practical puposes"
        return -999999.99; //returning -999999.99, which is the value the main function reads as an improper input
    }

    for (i = 0; i < str.length(); i++){ //for loop that iterates through all the characters in the string from main
        char currentCharacter = str[i]; //currentCharacter is a char variable that takes on the value of the character at index 'i' in the string. This variable will be changed for every iteration of this for loop, but is used to help determine if a string is valid

        if (i == 0 && (currentCharacter == '+' || currentCharacter == '-')){ //if statement that checks to see if the first charcter of the entered string is a positive or negative sign. This is important as it determines whether or not the outputted number is positive or negative. Index 0 is checked because a sign can only occur here in a valid number
            negativeNumber = (currentCharacter == '-'); //the boolean variable negativeNumber is determined here based on the sign erad by currentCharacter at index 0. If the sign is negative(-), then the boolean value of negativeNumber will change to true, meaning the number is negative. Otherwise, negativeNumber will stay false, meaning the number is positive 
            continue; //similar to a break, this tells the program to move on in the program, but without ending the program. In this case, it moves on to the next if statement
        }

        if (validNumbers.find(currentCharacter) != validNumbers.end()){ //check to see if the current character is in validNumbers list, with the exception of a plus(+) or minus(-) sign at index 0 since that is checked previously. This also doesn't account for a decimal point, as that will be checked next separately. 
            numInSet = true; //this means that the number at the current index of currentCharacter is a numerical value (0-9)
            if (numDecimals == 0){ //checks to see if there is already a decimal encountered in the string. If there is, this numerical value will be added to the decimal side. If there isn't, the number will be a part of the non-decimal side. Essentially this determines how the converted output is generated
                output = (output * 10) + (currentCharacter - '0'); //this changes the output of the previous iteration by adding an additional place(multiplying the result by 10) and adding the new number in as the result of the currentCharacter value minus the string version of zero. Example: if ouptut is 12 before this iteration and current value is 3, then output *10 = 120 and +('3'-'0') gets 123
            }
            else{ //this means there has already been a decimal point encountered, so the number at the current index of currentCharacter will be used to change the decimal value of the output
                output += (currentCharacter - '0') * decimal; //sets the output to the current output, plus the difference of currentCharacter - 0 times the current value of the decimal variable(starts at .1) 
                decimal = (decimal/10); //the value of the decimal variable is changed to account for the next number which will go to the hundreths, thousandths, etc.
            }
        }
        else if (currentCharacter == '.'){ //as mentioned in the comment at the if-statement of validNumbers.find, the decimal point case of currentCharacter gets a separate check, since it needs to update the count for numDecimals
            numDecimals++; //increases the count of numDecimals by 1
            if(numDecimals > 1){ //if statement that checks to see if numDecimals exceeds the allowed amount (0 or 1)
                return -999999.99; //returning -999999.99, which is the value the main function reads as an improper input
            }
        }
        else{ //this statement handles all other possible character values that are not accounted for in the previous 'main' if statements
            return -999999.99; //returning -999999.99, which is the value the main function reads as an improper input
        }
    }

    if(numInSet == true){ //makes sure there is no invalid numbers in the output, by checking that the boolean numInSet is true
        if(negativeNumber == false){ //checks to see if negativeNumber is false, meaning the output is positive
            return output; //returns the standard, positive version of the output
        }
        else{ //this statement is for when negativeNumber is true, meaning the output should be negative
            return (output * -1); //returns the negative version of the output by multiplying the output by -1
        }
    }
    else{ //this statement means that the string entered by the user contained an invalid character, and thus should not get a valid output
        return -999999.99; //returning -999999.99, which is the value the main function reads as an improper input
    }
}

int main(){
    string input; //input variable defined as a string. This variable will be assigned to the input from the user when promped to enter a string

    while (true){ //while true loop means this section of code will run infinitely, unless broken by the break condition inside of it(in this case the text input 'END')
        cout << "Enter a string (or 'END' to quit): "; //Output with instructions for the user on what input to enter 
        cin >> input; //takes in the user's input to the variable input defined above

        if (input == "END"){ //checks to see if the user inputted the break condition phrase 
            break; //If so, break the while loop, and therefore end the entire program
        }

        double number = extractNumeric(input); //number is defined as a double precision variable of the numerical version of the inputted string, so long as it's a valid number

        if (number != -999999.99){ //checks to see if the extractNumeric function does not return -999999.99, which is the return value of a non-numerical string input
            cout << "The input is: " << fixed << setprecision(4) << number << endl; //if the returned value is valid, then the input is given as a 4 decimal place value
        }
        else{ //else statement that runs if the returned value of extractNumeric is the non-numeric code '-999999.99'
            cout << "The input is invalid." << endl; //print statement that tells the user the string they entered is not a valid number
        }
    }
    return 0;
}


