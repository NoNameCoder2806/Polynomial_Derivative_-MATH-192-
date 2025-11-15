// Student: Dat Hoang Vien
// Course: MATH-192

// Libraries and headers
#include <iostream>
#include <numeric>
#include <string>
using namespace std;

// Polynomial class
class Term
{
private:
    string variable;             // The variable symbol / stringacter
    string coefficient;          // The coefficient of the Term
    int exponent;                // The exponent of the Term
    int sign;                    // The sign of the Term (positive: 1 or negative: -1)

public:
    // Constructor
    Term(string var = "x", string coe = "1", int p = 1, int s = 1)
    {
        variable = var;
        coefficient = coe;
        exponent = p;
        sign = s;
    }

    // Accessors / Getters
    string getVariable() const
    {
        return variable;
    }

    string getCoefficient() const
    {
        return coefficient;
    }

    int getExponent() const
    {
        return exponent;
    }

    int getSign() const
    {
        return sign;
    }

    // Mutators / Setters
    void setVariable(string var)
    {
        variable = var;
    }
    
    void setCoefficient(string coe)
    {
        coefficient = coe;
    }

    void setExponent(int p)
    {
        exponent = p;
    }

    void setSign(int s)
    {
        sign = s;
    }

    // Multiply() function
    void multiply(string &coefficient, int num)
    {
        // We try to find the / and . to see if this is a fraction or decimal value or not
        int slash = coefficient.find("/");
        int dot = coefficient.find(".");

        // If i == npos it means we couldn't find any / and . => not a fraction or decimal => integer
        if (slash == string::npos && dot == string::npos)
        {
            // Convert the string to an integer
            int coe = stoi(coefficient);

            // Multiply the coefficient with the number we passed into the function
            coe *= num;

            // Convert it back to a string
            coefficient = to_string(coe);
        }
        // If we found a . but not a / => this is a decimal value
        else if (slash == string::npos && dot != string::npos)
        {
            // Convert the string to a double
            double coe = stod(coefficient);

            // Multiply the coefficient with the number we passed into the function
            coe *= double (num);

            // Convert it back to a string
            coefficient = to_string(coe);

            // Clean the 0s
            while (coefficient.back() == '0')
            {
                // Remove the last stringacter
                coefficient.pop_back();
            }
        }
        // If we found a / but not a . => this is an integer / integer fraction
        else if (slash != string::npos && dot == string::npos)
        {
            // Convert the numerator and the denominator
            int numerator = stoi(coefficient.substr(0, slash));
            int denominator = stoi(coefficient.substr(slash + 1));

            // Multiply the numerator by num
            numerator *= num;

            // Find the greatest common divisor
            int g = gcd(numerator, denominator);
            
            // Divide both the numerator and the denominator by the greatest common divisor
            numerator /= g;
            denominator /= g;

            // Convert it back to a string
            if (denominator == 1)
            {
                if (numerator == 1)
                {
                    // No need to put anything in front of x
                    coefficient = "";
                }
                else
                {
                    // Convert the numerator to a string
                    coefficient = to_string(numerator);
                }
            }
            else
            {
                // Convert the numerator and the denominator
                coefficient = to_string(numerator) + "/" + to_string(denominator);
            }
        }
    }

    // Gcd() function
    int gcd(int a, int b)
    {
        if (b == 0)
        {
            return abs(a);
        }

        return gcd(b, a % b);
    }

    // Derivative() function
    void derivative()
    {
        // If the exponent is not 0, we will need to calculate the derivative
        if (exponent > 0)
        {
            // Decrease the exponent by 1
            exponent = exponent - 1;

            // Multiply the coefficient by the original exponent
            multiply(coefficient, exponent + 1);
        }
        // Otherwise (if the exponent is 0) then this is a number
        else
        {
            // Therefore, the derivative will be 0
            coefficient = "";
            exponent = 0;
            sign = 0;
        }
    }

    // ToString() function: convert the Term to a string
    string toString()
    {
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
        fullTerm += coefficient;

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

        // Return the string
        return fullTerm;
    }

    // DebugInfo() function
    void debugInfo()
    {
        // Display all the data of the Term
        cout << "Sign: " << (sign == 1 ? "+" : "-") << endl;
        cout << "Coefficient: " << (coefficient.length() == 0 ? "1" : coefficient) << endl;
        cout << "Variable: " << variable << endl;
        cout << "Exponent: " << exponent << endl;
    }
};