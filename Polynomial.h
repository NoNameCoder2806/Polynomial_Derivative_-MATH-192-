// Student: Dat Hoang Vien
// Course: MATH-192

// Libraries and headers
#include <iostream>
#include <vector>
#include "Term.h"
using namespace std;

// Polynomial class
class Polynomial
{
private:
    string functionSymbol;
    string variable;
    vector<Term> polynomial;

public:
    // Constructor
    Polynomial(vector<Term> poly = {}, string f = "f", string x = "x")
    {
        functionSymbol = f;
        variable = x;
        polynomial = poly;
    }

    // Accessors / Getters
    vector<Term> getPolynomial() const
    {
        return polynomial;
    }

    string getFunctionSymbol() const
    {
        return functionSymbol;
    }

    string getVariable() const
    {
        return variable;
    }

    // Mutators / Setters
    void setPolynomial(vector<Term> poly)
    {
        polynomial = poly;
    }

    void setFunctionSymbol(string fs)
    {
        functionSymbol = fs;
    }

    void setVariable(string v)
    {
        variable = v;
    }

    // AddTerm() function
    void addTerm(Term t)
    {
        polynomial.push_back(t);
    }

    // Derivative() function
    void derivative()
    {
        // Create a new vector
        vector<Term> newPoly;

        // Iterate through each of the Terms in the vector
        for (Term a : polynomial)
        {
            // Take the derivative
            a.derivative();

            // Add them to the new vector
            newPoly.push_back(a);
        }

        // Copy the new vector
        polynomial = newPoly;
    }

    // ToString() function
    string toString()
    {
        string str = "";

        str += functionSymbol + "(" + variable + ") = ";

        string poly = "";

        for (int i = 0; i < polynomial.size(); i++)
        {
            poly += polynomial.at(i).toString();
        }

        if (poly.size() > 1 && poly.at(1) == '+')
        {
            poly = poly.substr(3);
        }

        if (poly.length() == 0)
        {
            poly = "0";
        }

        return str + poly;
    }
};