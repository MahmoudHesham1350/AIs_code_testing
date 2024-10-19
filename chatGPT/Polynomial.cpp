
#include "Polynomial.h"

// Constructors
Polynomial::Polynomial() : coeffs(1, 0.0) {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& other) const {
    size_t maxSize = max(coeffs.size(), other.coeffs.size());
    vector<double> result(maxSize, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i) {
        result[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result[i] += other.coeffs[i];
    }

    return Polynomial(result);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    size_t maxSize = max(coeffs.size(), other.coeffs.size());
    vector<double> result(maxSize, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i) {
        result[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result[i] -= other.coeffs[i];
    }

    return Polynomial(result);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);

    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0)
                out << "+";
            out << poly.coeffs[i];
            if (i > 0) out << "x^" << i << " ";
        }
    }
    return out;
}

// Utility functions

int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result({0.0}); // Initialized as zero polynomial
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial({coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() == 1) return Polynomial({0});
    vector<double> deriv(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        deriv[i - 1] = i * coeffs[i];
    }
    return Polynomial(deriv);
}

Polynomial Polynomial::integral() const {
    vector<double> integ(coeffs.size() + 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        integ[i + 1] = coeffs[i] / (i + 1);
    }
    return Polynomial(integ);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = this->integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) const{
    Polynomial deriv = this->derivative();
    for (int i = 0; i < maxIter; ++i) {
        double y = evaluate(guess);
        double yPrime = deriv.evaluate(guess);
        if (abs(yPrime) < tolerance) break; // Prevent division by zero
        double nextGuess = guess - y / yPrime;
        if (abs(nextGuess - guess) < tolerance) return nextGuess;
        guess = nextGuess;
    }
    return guess;
}

Polynomial Polynomial::deflate(double root) const {
    vector<double> deflated(coeffs.size() - 1, 0.0);
    deflated.back() = coeffs.back();

    for (int i = coeffs.size() - 2; i >= 0; --i) {
        deflated[i] = coeffs[i + 1] + root * deflated[i + 1];
    }

    return Polynomial(deflated);
}


vector<double> Polynomial::getRoots(double tolerance, int maxIter) const {
    vector<double> roots;
    Polynomial p = *this; // Start with the original polynomial

    while (p.degree() > 0) {
        // Use Newton's method to find a root
        double root = p.getRoot(0.0, tolerance, maxIter); // Start guessing at x = 0

        // Deflate the polynomial by dividing it by (x - root)
        if (abs(p.evaluate(root)) < tolerance) {
            roots.push_back(root);
            p = p.deflate(root);
        } else {
            break; // No more roots can be found
        }
    }
    return roots;
}


// Set coefficients
void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

// Get coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= static_cast<int>(coeffs.size())) {
        return 0;
    }
    return coeffs[degree];
}

string Polynomial::toString() const {
    string result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        if (coeffs[i] != 0) {
            // Add a '+' if it's not the first term and the coefficient is positive
            if (i != coeffs.size() - 1 && coeffs[i] > 0)
            {
                result += " + ";
                // Add the coefficient
                result += to_string((int)coeffs[i]);
            }
            else if (i != coeffs.size() - 1 && coeffs[i] < 0){
                result += " - " + to_string((int)abs(coeffs[i]));
            }
            else {
                // Add the coefficient
                result += to_string((int) coeffs[i]);
            }

            // Add the variable part
            if (i > 0)
                result += "*x" + (i == 1 ? "" : "^" + to_string(i));
        }
    }
    return result;
}






