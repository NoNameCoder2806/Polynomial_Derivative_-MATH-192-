// Student: Dat Hoang Vien
// Course: MATH-192
// Assignment: Capturing Math Through Art

// Libraries and headers
#include <iostream>
#include <numeric>
#include <string>
#include "Term.h"
using namespace std;

// Constructor
Term::Term(string var, string coe, int p, int s, bool ne)
{
    variable = var;
    coefficient = coe;
    exponent = p;
    sign = s;
    negativeExponent = ne;
}

// Accessors / Getters
string Term::getVariable() const { return variable; }
string Term::getCoefficient() const { return coefficient; }
int Term::getExponent() const { return exponent; }
int Term::getSign() const { return sign; }
bool Term::getNegativeExponent() const { return negativeExponent; }

// Mutators / Setters
void Term::setVariable(string var) { variable = var; }
void Term::setCoefficient(string coe) { coefficient = coe; }
void Term::setExponent(int p) { exponent = p; }
void Term::setSign(int s) { sign = s; }
void Term::setNegativeExponent(bool ne) { negativeExponent = ne; }

// Operator<()
bool Term::operator<(const Term &other)
{
    // Compare the exponents of the Terms
    return this->exponent < other.exponent;
}

// Multiply() function
void Term::multiply(string &coefficient, int num)
{
    // Check whether the coefficient is empty
    if (coefficient.empty())
    {
        coefficient = "1";
    }

    // We try to find the / and . to see if this is a fraction or decimal value or not
    int slash = coefficient.find("/");
    int dot = coefficient.find(".");

    // Find constant characters in the numerator and denominator
    string numChar = "";
    string denomChar = "";

    // Iterate and find all the characters
    for (int i = 0; i < coefficient.length();)
    {
        // If we find a character
        if (isalpha(coefficient.at(i)))
        {
            // We compare its position to the position of the /
            if (i > slash  && slash != string::npos)
            {
                // If it comes after the /, we add it to the denominator
                denomChar += coefficient.at(i);
            }
            else
            {
                // Otherwise, we add it to the numerator
                numChar += coefficient.at(i);
            }

            // Remove the character from the coefficient
            coefficient.erase(i, 1);

            // Check whether the coefficient is now empty
            if (coefficient.empty())
            {
                // Break out of the loop
                break;
            }
        }
        else
        {
            // We only increment if the character is not found
            i++;
        }
    }

    // Split the coefficient into the numerator and denominator
    string numeratorString = "";
    string denominatorString = "";

    // Check whether the / exists
    if (slash != string::npos)
    {
        // If it does, we split the numerator and denominator
        numeratorString = coefficient.substr(0, slash);
        denominatorString = coefficient.substr(slash + 1);
    }
    else
    {
        // If the slash does not exist
        numeratorString = coefficient;
    }

    // Check whether the numerator is empty
    if (numeratorString.empty())
    {
        // If it is, we let the numeratorString be 1
        numeratorString = "1";
    }

    // Check whether the denominator is empty
    if (denominatorString.empty())
    {
        // If it is, we let the denominatorString be 1
        denominatorString = "1";
    }

    // If i == npos it means we couldn't find any / and . => not a fraction or decimal => integer
    if (slash == string::npos && dot == string::npos)
    {
        // Convert the string to an integer
        int coe = stoi(numeratorString);

        // Multiply the coefficient with the number we passed into the function
        coe *= num;

        // No constant characters
        if (numChar.length() == 0)
        {
            // Only add the number
            coefficient = to_string(coe);
        }
        else          // Have at least 1 constant character
        {
            // Check whether the coefficient is 1
            if (coe == 1)
            {
                // Only add the character
                coefficient = numChar;
            }
            else          // Otherwise
            {
                // Convert it back to a string and add the constant characters
                coefficient = to_string(coe) + numChar;
            }
        }
    }
    // If we found a . but not a / => this is a decimal value
    else if (slash == string::npos && dot != string::npos)
    {
        // Convert the string to a double
        double coe = stod(numeratorString);

        // Multiply the coefficient with the number we passed into the function
        coe *= double (num);

        // Convert it back to a string
        string coefficientString = to_string(coe);

        // Clean the 0s and the .
        while (coefficientString.back() == '0' || coefficientString.back() == '.')
        {
            // Remove the last string
            coefficientString.pop_back();
        }

        // No constant characters
        if (numChar.length() == 0)
        {
            // Only add the number
            coefficient = coefficientString;
        }
        else          // Have at least 1 constant character
        {
            // Check whether the coefficient is 1
            if (coefficientString == "1")
            {
                // Only add the character
                coefficient = numChar;
            }
            else          // Otherwise
            {
                // Convert it back to a string and add the constant characters
                coefficient = coefficientString + numChar;
            }
        }
    }
    // If we found a / but not a . => this is an integer / integer fraction
    else if (slash != string::npos && dot == string::npos)
    {
        // Convert the numerator and the denominator
        int numerator = stoi(numeratorString);
        int denominator = stoi(denominatorString);

        // Multiply the numerator by num
        numerator *= num;

        // Find the greatest common divisor
        int g = Term::gcd(numerator, denominator);
        
        // Divide both the numerator and the denominator by the greatest common divisor
        numerator /= g;
        denominator /= g;

        // Convert it back to a string
        if (denominator == 1)
        {
            if (numerator == 1)
            {
                // Only add constants characters
                coefficient = numChar;
            }
            else
            {
                // Convert the numerator to a string and add constants characters
                coefficient = to_string(numerator) + numChar;
            }

            if (denomChar.length() > 0)
            {
                // Add the denominator in
                coefficient += "/" + denomChar;
            }
        }
        else
        {
            // Convert the numerator and the denominator
            coefficient = to_string(numerator) + numChar + "/" + to_string(denominator) + denomChar;
        }
    }
}

// Gcd() function
int Term::gcd(int a, int b)
{
    if (b == 0)
    {
        return abs(a);
    }

    return gcd(b, a % b);
}

// Derivative() function
void Term::derivative()
{
    // If this is a negative exponent
    if (negativeExponent)
    {
        // Add the exponent by 1 because the exponent is only a positive value
        exponent = exponent + 1;

        // Check for negative exponent
        if (negativeExponent)
        {
            // Switch the sign
            sign = (-1) * sign;
        }

        // Multiply the coefficient by the original exponent
        multiply(coefficient, exponent - 1);
    }
    else
    {
        // If the exponent is not 0, we will need to calculate the derivative
        if (exponent > 1)
        {
            // Decrease the exponent by 1
            exponent = exponent - 1;

            // Multiply the coefficient by the original exponent
            multiply(coefficient, exponent + 1);
        }
        // If the exponent is 1
        else if (exponent == 1)
        {
            // Keep the coefficient, only decrease the exponent by 1
            exponent = exponent - 1;
        }
        // Otherwise (if the exponent is 0) then this is a number
        else if (exponent == 0)
        {
            // Therefore, the derivative will be 0
            coefficient = "";
            exponent = 0;
            sign = 0;
        }
    }
}

// ToString() function: convert the Term to a string
string Term::toString()
{
    // Check whether the coefficient is 0
    if (coefficient == "0")
    {
        return "";
    }

    // Create a variable to store the whole string sequence
    string fullTerm = "";

    // If the sign is negative, we add a - to the front
    if (sign == -1)
    {
        fullTerm += " - ";
    }
    // Otherwise, we add a + to the front
    else if (sign == 1)
    {
        fullTerm += " + ";
    }

    // Then, we add the coefficient to the Term
    if (coefficient != "1" && exponent >= 0)
    {
        fullTerm += coefficient;
    }

    // Display negative exponent
    if (negativeExponent)
    {
        fullTerm += variable + "^-" + to_string(exponent);
    }
    else
    {
        // If the exponent is 0, we ignore it
        if (exponent == 0)
        {
            ;
        }
        // If the exponent is 1, we only add the variable to the string
        else if (exponent == 1)
        {
            fullTerm += variable;
        }
        // Otherwise, we add the variable and the exponent
        else
        {
            fullTerm += variable + "^" + to_string(exponent);
        }
    }

    // Return the string
    return fullTerm;
}

// DebugInfo() function
void Term::debugInfo()
{
    // Display all the data of the Term
    cout << "Sign: " << (sign == 1 ? "+" : "-") << endl;
    cout << "Coefficient: " << (coefficient.length() == 0 ? "1" : coefficient) << endl;
    cout << "Variable: " << variable << endl;
    cout << "Exponent: " << exponent << endl;
    cout << "Negative Exponent: " ;
    if (negativeExponent) 
    {
        cout << "True" << endl;
    }
    else 
    {
        cout << "False" << endl;
    }
}