// Student: Dat Hoang Vien
// Course: MATH-192
// Assignment: Capturing Math Through Art

// Libraries and headers
#include <iostream>
#include <vector>
#include "Polynomial.h"
using namespace std;

// Constructor
Polynomial::Polynomial(vector<Term> poly, string f, string x, int d)
{
    functionSymbol = f;
    variable = x;
    polynomial = poly;
    derivativeOrder = d;
}

// Accessors / Getters
vector<Term> Polynomial::getPolynomial() const { return polynomial; }
string Polynomial::getFunctionSymbol() const { return functionSymbol; }
string Polynomial::getVariable() const { return variable; }
int Polynomial::getDerivativeOrder() const { return derivativeOrder; }

// Mutators / Setters
void Polynomial::setPolynomial(vector<Term> poly) { polynomial = poly; }
void Polynomial::setFunctionSymbol(string fs) { functionSymbol = fs; }
void Polynomial::setVariable(string v) { variable = v; }
void Polynomial::setDerivativeOrder(int dl) { derivativeOrder = dl; }

// AddTerm() function
void Polynomial::addTerm(Term t)
{
    polynomial.push_back(t);
}

// Derivative() function
void Polynomial::derivative()
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
string Polynomial::toString()
{
    string func = "";

    if (derivativeOrder == 0)
    {
        func += functionSymbol + "(" + variable + ") = ";
    }
    else if (derivativeOrder <= 3)
    {
        func += functionSymbol;

        // Display all the '
        for (int i = 0; i < derivativeOrder; i++)
        {
            func += "'";
        }

        func += "(" + variable + ") = ";
    }
    else
    {
        func += functionSymbol + "(" + to_string(derivativeOrder) + ")" + "(" + variable + ") = ";
    }

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

    return func + poly;
}

// Sort() function
void Polynomial::sort()
{
    // Use bubble sort to rearrange the Terms
    for (int i = 0; i < polynomial.size(); i++)
    {
        for (int j = 0; j < polynomial.size() - 1; j++)
        {
            if (polynomial.at(j) < polynomial.at(j + 1))
            {
                Term temp = polynomial.at(j);
                polynomial.at(j) = polynomial.at(j + 1);
                polynomial.at(j + 1) = temp;
            }
        }
    }
}