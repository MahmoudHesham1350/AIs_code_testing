//
// Created by Mahmoud on 10/18/2024.
//

#ifndef TASK2_POLYNOMIAL_H
#define TASK2_POLYNOMIAL_H


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial();
    Polynomial(const vector<double>& coefficients);
    Polynomial(const Polynomial& other);

    // Destructor
    ~Polynomial();

    // Assignment operator
    Polynomial& operator=(const Polynomial& other);

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;

    // Equality operator
    bool operator==(const Polynomial& other) const;

    // Output operator
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

    // Utility functions
    int degree() const; // Return the degree of the polynomial

    double evaluate(double x) const; // Evaluate the polynomial at x

    Polynomial compose(const Polynomial& q) const; // Composition

    Polynomial derivative() const; // Derivative of the polynomial

    Polynomial integral() const; // Return a polynomial of integration

    double integral(double x1, double x2) const; // Intergate from x1 to x2

    // Get roots of the polynomial
    vector<double> getRoots(double tolerance = 1e-6, int maxIter = 1000) const;

    // Helper functions for roots
    double getRoot(double guess, double tolerance, int maxIter) const;
    Polynomial deflate(double root) const;

    void setCoefficients(const vector<double>& coefficients);   // Set coefficients

    // String representation
    string toString() const;

    double getCoefficient(int degree) const;    // Get coefficient of a specific degree

};


#endif //TASK2_POLYNOMIAL_H
