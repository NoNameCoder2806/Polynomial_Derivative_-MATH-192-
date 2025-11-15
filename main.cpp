// Student: Dat Hoang Vien
// Course: MATH-192

// Libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "Polynomial.h"
using namespace std;

// Function prototypes
bool checkFunction(string data);
void reformatString(string &data);
Term createTerm(string data, string variable);
Polynomial createPolynomial(string data);

int main()
{
    string line = "";
    char choice = 'Y';
    int order = 0;

    // Create a loop to run the program
    while (toupper(choice) == 'Y')
    {
        // Prompt the user to enter a function
        cout << "Enter a polynomial:" << endl;
        getline(cin, line);

        // Create the polynomial
        Polynomial f = createPolynomial(line);

        // Prompt the user to enter the order of the derivative
        cout << "Enter the derivative order: ";
        cin >> order;
        cin.ignore(1000, 10);

        // Loop and calculate the derivative
        for (int i = 0; i < order; i++)
        {
            // Take the derivative
            f.derivative();
        }

        // Display the result
        cout << "Result: " << f.toString() << endl;

        // Ask the user whether they want to run the program again
        cout << "Do you want to enter another function? (Y/N): ";
        cin >> choice;
        cin.ignore(1000, 10);
    }

    // Display a message
    cout << "Thank you for using the program! Exiting..." << endl;

    return 0;
}

// Function implementations
bool checkFunction(string data)
{
    // Check to see whether the string is a valid function
    // Find the positions of =, (, )
    int pos1 = data.find('(');
    int pos2 = data.find(')');
    int pos3 = data.find('=');

    // To be a function, the entered string must satisfy these conditions
    // 1. The =, (, ) must exist
    if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
    {
        // Display a message
        cout << "A function must have a '=', '(', and ')'!" << endl;

        return false;
    }

    // 2. The ( must come before the ) and the ) must come before the =
    if (pos1 > pos2 || pos1 > pos3 || pos2 > pos3)
    {
        // Display a message
        cout << "In a function, the '(' must come before the ')', and then ')' must come before the '='!" << endl;
        
        return false;
    }

    // 3. There must be at least 1 character before the (
    if (pos1 < 1)
    {
        // Display a message
        cout << "You did not enter the function's symbol!" << endl;

        return false;
    }

    // 4. There must be at least 1 character between inside the ()
    if (pos1 + 1 == pos2)
    {
        // Display a message
        cout << "You did not enter the variable!" << endl;

        return false;
    }

    // 5. If there is no number / character after the = (no term)
    bool numCharExist = false;
    string right = data.substr(pos3);

    for (int i = 0; i < right.length(); i++)
    {
        if (isalnum(right.at(i)))
        {
            numCharExist = true;
        }
    }
    
    if (!numCharExist)
    {
        // Display a message
        cout << "Your function must have a number or character after the =!" << endl;

        return false;
    }

    // If it satisfy all of the conditions, we return true
    return true;
}

void reformatString(string &data)
{
    // Remove all the spaces in the string
    data.erase(remove(data.begin(), data.end(), ' '), data.end());

    int i = 0;

    // Deal with the signs
    while (true)
    {
        // Turn ++ into just +
        i = data.find("++");
        if (i != string::npos)
        {
            data = data.substr(0, i) + "+" + data.substr(i + 1);
            continue;
        }

        // Turn -- into +
        i = data.find("--");
        if (i != string::npos)
        {
            data = data.substr(0, i) + "+" + data.substr(i + 1);
            continue;
        }

        // Turn -+ into -
        i = data.find("+-");
        if (i != string::npos)
        {
            data = data.substr(0, i) + "-" + data.substr(i + 1);
            continue;
        }

        // Turn +- into -
        i = data.find("-+");
        if (i != string::npos)
        {
            data = data.substr(0, i) + "-" + data.substr(i + 1);
            continue;
        }

        // Break out of the loop if these cases are not met
        break;
    }
}

Term createTerm(string data, string variable)
{
    if (data.length() == 0 || variable.length() == 0)
    {
        // Display an error message
        cerr << "Error: Invalid term format." << endl;
        exit(1);          // Exit the function
    }

    // Create variables to use
    int sign = 1;
    string coefficient = "";
    int exponent = 0;

    // Check the sign
    if (data.at(0) == '-')
    {
        // Negative sign
        sign = -1;

        // Decrease the string size
        data = data.substr(1);
    }
    else if (data.at(0) == '+')
    {
        // Positive sign
        sign = 1;

        // Decrease the string size
        data = data.substr(1);
    }
    else
    {
        // Also positive sign (first term of the polynomial)
        sign = 1;
    }

    // Find the variable position
    int varPos = data.find(variable);

    // If not found
    if (varPos == string::npos)
    {
        // Then the exponent is 0 (ax^0 = a)
        exponent = 0;

        // And the whole remaining string is the coefficient
        coefficient = data;
    }
    // If found, the exponent is >= 1
    else
    {
        // Find the ^ symbol
        int expoPos = data.find('^');

        // If not found
        if (expoPos == string::npos)
        {
            // Then the exponent is 1
            exponent = 1;

            // Take everything from the start to the variable position
            coefficient = data.substr(0, varPos);
        }
        // If found, the exponent is larger than 1
        else
        {
            // Take everything from the ^ to the end of the string
            exponent = stoi(data.substr(expoPos + 1));
            
            // Take everything from the start to the variable
            coefficient = data.substr(0, varPos);
        }
    }

    // Create the Term
    Term t(variable, coefficient, exponent, sign);

    // Return the Term
    return t;
}

Polynomial createPolynomial(string data)
{
    // Reformat the string
    reformatString(data);

    // Find the position of the (, ), =
    int pos1 = data.find('(');
    int pos2 = data.find(')');
    int pos3 = data.find('=');

    // Get the function symbol and the variable
    string func = data.substr(0, pos1);                            // Everything before '('
    string var  = data.substr(pos1 + 1, pos2 - pos1 - 1);          // Everything between '(' and ')'
    string terms = data.substr(pos3 + 1);                          // Everything from '=' to the end
    
    // Create a vector and an integer to store all the Terms and the sign of the Term
    vector<Term> termsVector = {};
    int sign = 1;

    // A boolean to keep the loop running
    bool reading = true;

    // Read all the terms
    while (terms.length() != 0)
    {
        // If it is the first term and has a positive sign (or no sign, because it's the 1st term)
        if (termsVector.size() == 0 && terms.at(0) != '-')
        {
            // Find the ending position of the term by finding the first + or -
            int first = terms.find_first_of("+-");

            // Create and add the Term to the vector
            termsVector.push_back(createTerm(terms.substr(0, first), var));

            if (first != string::npos)
            {
                // Trim the string
                terms = terms.substr(first);
            }
        }
        else
        {
            // Find the ending position of the term
            int first = terms.find_first_of("+-");                      // Find the first sign
            int second = terms.find_first_of("+-", first + 1);          // Find the second sign

            if (second != string::npos)
            {
                // Split the string and create the Term
                termsVector.push_back(createTerm(terms.substr(first, second - first), var));

                // Trim the string
                terms = terms.substr(second);
            }
            else
            {
                // Split the string and create the Term
                termsVector.push_back(createTerm(terms, var));

                // This is the last term
                terms = "";
            }
        }
    }

    // Create a polynomial
    Polynomial f(termsVector, func, var);

    return f;
}