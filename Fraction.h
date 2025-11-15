// Student: Dat Hoang Vien

// Libraries
#include <iostream>
#include <string>
using namespace std;

// Fraction class
class Fraction
{
private:
    int numerator;
    int denominator = 1;

public:
    // Constructors
    Fraction()
    {
        numerator = 1;
        denominator = 1;
    }

    Fraction(int nom)
    {
        numerator = nom;
        denominator = 1;
    }

    Fraction(int nom, int denom)
    {
        numerator = nom;

        if (denom != 0)
        {
            denominator = denom;
        }
        else
        {
            denominator = 1;
        }
    }

    // Accessors / Getters
    int getnumerator() const
    {
        return numerator;
    }

    int getdenominator() const
    {
        return denominator;
    }

    // Mutators / Setters
    void setnumerator(int nom)
    {
        numerator = nom;
    }

    void setdenominator(int denom)
    {
        denominator = denom;
    }

    // ToString() function
    string toString()
    {
        if (numerator == 0)
        {
            return "0";
        }

        if (denominator == 1)
        {
            return to_string(numerator);
        }
        else if (denominator != 0)
        {
            return to_string(numerator) + "/" + to_string(denominator);
        }
    }
};