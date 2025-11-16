// Student: Dat Hoang Vien
// Course: MATH-192
// Assignment: Capturing Math Through Art

#pragma once

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
    Term(string var = "x", string coe = "1", int p = 1, int s = 1);

    // Accessors / Getters
    string getVariable() const;
    string getCoefficient() const;
    int getExponent() const;
    int getSign() const;

    // Mutators / Setters
    void setVariable(string var);
    void setCoefficient(string coe);
    void setExponent(int p);
    void setSign(int s);

    // Operator<()
    bool operator<(const Term &other);

    // Multiply() function
    void multiply(string &coefficient, int num);

    // Gcd() function
    static int gcd(int a, int b);

    // Derivative() function
    void derivative();

    // ToString() function: convert the Term to a string
    string toString();

    // DebugInfo() function
    void debugInfo();
};