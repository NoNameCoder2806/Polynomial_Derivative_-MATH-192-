// Student: Dat Hoang Vien
// Course: MATH-192
// Assignment: Capturing Math Through Art

#pragma once

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
    Polynomial(vector<Term> poly = {}, string f = "f", string x = "x");

    // Accessors / Getters
    vector<Term> getPolynomial() const;
    string getFunctionSymbol() const;
    string getVariable() const;

    // Mutators / Setters
    void setPolynomial(vector<Term> poly);
    void setFunctionSymbol(string fs);
    void setVariable(string v);

    // AddTerm() function
    void addTerm(Term t);

    // Derivative() function
    void derivative();

    // ToString() function
    string toString();

    // Sort() function
    void sort();
};