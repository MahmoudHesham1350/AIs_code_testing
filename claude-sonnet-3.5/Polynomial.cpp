#include "Polynomial.h"
#include <sstream>

Polynomial::Polynomial() {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

Polynomial::~Polynomial() {}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result_coeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result_coeffs[i] += other.coeffs[i];
    }
    return Polynomial(result_coeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result_coeffs(max(coeffs.size(), other.coeffs.size()), 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        result_coeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        result_coeffs[i] -= other.coeffs[i];
    }
    return Polynomial(result_coeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result_coeffs(coeffs.size() + other.coeffs.size() - 1, 0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result_coeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result_coeffs);
}

bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    out << poly.toString();
    return out;
}

int Polynomial::degree() const {
    return coeffs.empty() ? -1 : coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial({coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    if (coeffs.size() <= 1) return Polynomial({0});
    vector<double> der_coeffs(coeffs.size() - 1);
    for (size_t i = 1; i < coeffs.size(); ++i) {
        der_coeffs[i-1] = coeffs[i] * i;
    }
    return Polynomial(der_coeffs);
}

Polynomial Polynomial::integral() const {
    vector<double> int_coeffs(coeffs.size() + 1);
    int_coeffs[0] = 0;  // Constant of integration
    for (size_t i = 0; i < coeffs.size(); ++i) {
        int_coeffs[i+1] = coeffs[i] / (i + 1);
    }
    return Polynomial(int_coeffs);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial int_poly = integral();
    return int_poly.evaluate(x2) - int_poly.evaluate(x1);
}

vector<double> Polynomial::getRoots(double tolerance, int maxIter) const {
    vector<double> roots;
    for (int i = -10; i <= 10; ++i) {
        double root = getRoot(i, tolerance, maxIter);
        if (root != i) {
            roots.push_back(root);
            Polynomial deflated = deflate(root);
            vector<double> deflated_roots = deflated.getRoots(tolerance, maxIter);
            roots.insert(roots.end(), deflated_roots.begin(), deflated_roots.end());
        }
    }
    return roots;
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) const {
    double x = guess;
    for (int i = 0; i < maxIter; ++i) {
        double x_new = x - evaluate(x) / derivative().evaluate(x);
        if (abs(x_new - x) < tolerance) {
            return x_new;
        }
        x = x_new;
    }
    return guess;
}

Polynomial Polynomial::deflate(double root) const {
    if (coeffs.empty()) return Polynomial();

    vector<double> result(coeffs.size() - 1);
    result[coeffs.size() - 2] = coeffs.back();

    for (int i = coeffs.size() - 2; i > 0; --i) {
        result[i-1] = coeffs[i] + result[i] * root;
    }

    // Remove leading zeros
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }

    return Polynomial(result);
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

string Polynomial::toString() const {
    ostringstream oss;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        if (coeffs[i] != 0) {
            if (i == 0) {
                oss << coeffs[i];
            } else if (i == 1) {
                oss << coeffs[i] << "x";
            } else {
                oss << coeffs[i] << "x^" << i;
            }
            if (i > 0) {
                oss << " + ";
            }
        }
    }
    return oss.str();
}

double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) {
        return 0;
    }
    return coeffs[degree];
}