//#include <iostream>
//#include "Polynomial.h"
//#include "gtest/gtest.h"
//
//class PolynomialTest : public ::testing::Test {
//protected:
//    Polynomial p1, p2;
//};
//struct PolynomialTestCase {
//    vector<double> poly1_coeffs;
//    vector<double> poly2_coeffs;
//    Polynomial expected_sum;
//    Polynomial expected_subtraction;
//    Polynomial expected_product;
//    int expected_degree;
//    double eval_x;
//    double expected_eval_poly1;
//    Polynomial expected_derivative;
//    double definite_integral;
//    vector<double> real_roots;
//
//    PolynomialTestCase() {
//        poly1_coeffs = {-7, -5, -13, 1, 5, 12, 2, -3, -14, -4, -9};
//        poly2_coeffs = {-10, -1, 7, -3, -12, -4, 12, 12, -8, 9};
//        expected_sum = Polynomial({-17, -6, -6, -2, -7, 8, 14, 9, -22, 5, -9});
//        expected_subtraction = Polynomial({3, -4, -20, 4, 17, 16, -10, -15, -6, -13, -9});
//        expected_product = Polynomial({70, 57, 86, -11, -43, 9, 92, -7, -103, -304, 64, 130, 266, 68, 12, -138, -71, -202, 36, -81});
//        expected_degree = 10;
//        eval_x = 2;
//        expected_eval_poly1 = -14701;
//        expected_derivative = Polynomial({-5, -26, 3, 20, 60, 12, -21, -112, -36, -90});
//        definite_integral = -372733.0 / 27720.0;
//        real_roots = {};
//    }
//};
//
//TEST_F(PolynomialTest, PolynomialOperations) {
//    PolynomialTestCase testCase;
//
//    Polynomial p1(testCase.poly1_coeffs);
//    Polynomial p2(testCase.poly2_coeffs);
//
//    // Test Sum
//    EXPECT_EQ(p1 + p2, testCase.expected_sum);
//
//    // Test Subtraction
//    EXPECT_EQ(p1 - p2, testCase.expected_subtraction);
//
//    // Test Multiplication
//    EXPECT_EQ(p1 * p2, testCase.expected_product);
//
//    // Test Degree
//    EXPECT_EQ(p1.degree(), testCase.expected_degree);
//
//    // Test Evaluation
//    double eval_result = p1.evaluate(testCase.eval_x);
//    EXPECT_DOUBLE_EQ(eval_result, testCase.expected_eval_poly1);
//
//    // Test Derivative
//    Polynomial deriv = p1.derivative();
//    EXPECT_EQ(deriv, testCase.expected_derivative);
//
//    // Test Definite Integral
//    double definite_integral = p1.integral(0, 1);
//    EXPECT_NEAR(definite_integral, testCase.definite_integral, 1e-9);
//
//    // Test Real Roots
//    vector<double> roots = p1.getRoots();
//    EXPECT_TRUE(roots.empty()); // Since there are no real roots in this test case
//}
//
//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}

#include <iostream>
#include <fstream>
#include "Polynomial.h"

struct input {
    int degree1;
    vector<double> coeffs1;
    int degree2;
    vector<double> coeffs2;
};

input arr[] = {
        // Test Case 1
        {10, {-7, -5, -13, 1, 5, 12, 2, -3, -14, -4, -9},
                9, {-10, -1, 7, -3, -12, -4, 12, 12, -8, 9}},
        // Test Case 2
        {8, {6, -2, 6, -4, 4, 1, 0, -13, -8},
                5, {-6, 9, -5, 9, 11, 15}},
        // Test Case 3
        {3, {-7, 13, -8, 8},
                7, {15, -2, 1, -4, 0, 14, -5, -6}},
        // Test Case 4
        {4, {-10, -12, 11, 5, -9},
                11, {-2, -2, 5, -8, 4, -5, 0, -6, 2, 1, 14, 13}},
        // Test Case 5
        {9, {-3, -8, -13, 5, 6, 13, -8, -5, -11, 8},
                3, {-11, -2, -3, -5}},
        // Test Case 6
        {0, {-11},
                4, {2, -12, -1, 15, 2}},
        // Test Case 7
        {9, {0, 4, -6, -4, 13, 12, 10, -1, -3, -3},
                2, {8, 3, -6}},
        // Test Case 8
        {9, {-3, -4, -14, -5, 11, -13, -14, 5, -13, -4},
                10, {8, -12, 9, -11, 12, -10, -12, 15, 11, 1, -9, 0}},
        // Test Case 9
        {10, {7, -7, 8, 12, 13, 11, 8, 8, 9, 9, -3},
                6, {14, -12, -10, -8, 2, -10, 4}},
        // Test Case 10
        {5, {10, -6, 2, -1, -10, 2},
                9, {12, 14, 12, 13, -5, 5, 9, 13, -5, 5}},
        // Test Case 11
        {9, {2, -2, -2, 9, -10, -12, 2, -10, -14, 5},
                7, {6, 0, -12, 4, -8, -2, 1, 4}},
        // Test Case 12
        {11, {11, 11, 8, -13, 15, 0, -13, -6, 3, 4, 6, 12},
                3, {-7, -2, 9, -13}},
        // Test Case 13
        {10, {5, -7, 13, 10, 2, 15, -8, -3, -14, -4, 10},
                9, {11, 3, 11, -14, 4, -8, 12, 6, -2, -7}},
        // Test Case 14
        {5, {9, -6, -14, -4, 3, -12},
                11, {2, 1, 1, 5, 6, -3, 12, 2, 7, 12, -13, 15}},
        // Test Case 15
        {7, {9, -4, -8, -5, 6, -3, 11, 5, 0},
                7, {4, -5 , -5, 4, 2, 6, -5, 1}},
        // Test Case 16
        {2, {14, 2, -1},
                10, {-4, 11, -7, -2, 10, -13, 11, 10, -13, -7, -6}},
        // Test Case 17
        {9, {-5, -1, 6, -1, -1, 4, 0, 2, -8, 2},
                4, {-2, -6, 11, -5, -4}},
        // Test Case 18
        {10, {12, 12, 10, -3, 8, -2, -11, -1, 11, 2, 11},
                2, {-1, -6, -12}},
        // Test Case 19
        {1, {-8, 3},
                7, {0, -4, 1, -11, -5, -8, -2, -3}},
        // Test Case 20
        {0, {3},
                7, {11, 1, 9, -13, 15, 2, -8, 14}},
        // Test Case 21
        {0, {4},
                11, {-7, 8, -8, 8, 6, -11, -9, -11, -4, -14, -4, 8}},
        // Test Case 22
        {6, {-14, 7, 15, 2, 4, 9, 15},
                3, {-8, 13, -12, -13}},
        // Test Case 23
        {1, {14, -14},
                3, {-7, 11, -10, 3}},
        // Test Case 24
        {6, {-13, 7, -12, 8, 1, 8, 10, 7, 6},
                3, {13, -12, -2, -2}},
        // Test Case 25
        {2, {-6, -1, 3},
                6, {10, -3, -1, 2, 15, -5, 14}},
        // Test Case 26
        {0, {12},
                9, {11, 5, 3, 12, 14, -2, -12, 11, -6, -14}},
        // Test Case 27
        {11, {-2, -5, 14, -1, -3, -8, 2, 14, 6, -5, -4, -8},
                10, {-12, -7, 7, 9, -9, -12, 2, -2, 14, -9, -11, 0}},
        // Test Case 28
        {1, {-1, -2},
                9, {-2, -9, 4, -9, -13, -10, 12, 4, 14, 9}},
        // Test Case 29
        {7, {-7, 15, -7, -4, 3, 3, 9, 8},
                3, {-9, -3, 0, 2}},
        // Test Case 30
        {6, {-10, 15, 6, -12, 14, 6, -14},
                10, {8, -3, -7, 7, -14, -11, 9, -3, -10, 3, 7}},
        // Test Case 31
        {3, {1, 7, -14, 1},
                2, {-9, 9, -11}},
        // Test Case 32
        {11, {7, -9, -9, -3, 10, 2, -14, -4, 6, -12, 10, 14},
                0, {6}},
        // Test Case 33
        {0, {-12},
                7, {13, 11, 8, 0, -6, -13, 5, 8}},
        // Test Case 34
        {5, {14, -4, -1, -5, 13, 14},
                9, {-3, -6, -6, -2, 15, -12, -12, -3, 12, -12}},
        // Test Case 35
        {0, {3},
                1, {13, 3}},
        // Test Case 36
        {9, {-6, -13, -9, 2, 8, 12, -1, 15, 2, -11},
                2, {-7, 4, 2}},
        // Test Case 37
        {4, {-14, 3, -5, -3, 5},
                8, {10, -13, -6, -9, 8, 0, -2, -6, 4}},
        // Test Case 38
        {3, {-6, -8, 6, 1},
                10, {-4, 1, -12, 3, -1, -1, 5, 12, 8, 9, 13}},
        // Test Case 39
        {1, {-7, 4},
                7, {-3, -5, 7, 14, 11, -7, 4, 5}},
        // Test Case 40
        {4, {4, -14, -12, 14, -11},
                9, {4, 11, -7, 2, 5, -2, 6, 9, -4, 1}},
        // Test Case 41
        {5, {-9, -12, -8, 10, -3, -9},
                2, {-7, -3, 13}},
        // Test Case 42
        {5, {-4, -7, -2, -5, 14, -5},
                7, {14, 15, -11, 4, -5, 13, -4, -5}},
        // Test Case 43
        {10, {-13, -5, 1, -9, 12, -3, 1, 9, -10, 1, -10},
                8, {5, 13, 4, 1, 11, 10, 7, -14, 8}},
        // Test Case 44
        {0, {9},
                7, {-7, -4, 10, -2, -13, -1, 5, 11}},
        // Test Case 45
        {9, {0, 1, 1, 15, -11, 7, 13, -7, 12, 0},
                1, {9, 4}},
        // Test Case 46
        {0, {11},
                0, {9}},
        // Test Case 47
        {10, {0, 13, 1, 10, 3, 15, -1, -5, -7, 8, 10},
                4, {11, 0, 2, 9, 13}},
        // Test Case 48
        {7, {12, -13, -6, -14, -1, 3, 0, -9},
                10, {-4, -14, 13, -8, -14, -7, -5, -9, -7, -11, -4}},
        // Test Case 49
        {5, {-8, 9, 2, -5, 5, 3},
                10, {15, 2, 12, -3, 9, -6, -3, 4, 13, -8, 4}},
        // Test Case 50
        {3, {11, -13, -4, -13},
                4, {-7, 10, 11, -1, -13}},
        // Test Case 51
        {4, {7, -5, 4, -1, 6},
                1, {-1, 10}},
        // Test Case 52
        {0, {5},
                7, {-14, 0, 10, -2, -8, -11, 11, -7}},
        // Test Case 53
        {11, {-9, -1, 14, 15, -13, 15, -12, -12, -5, 14, -7, 15},
                6, {-10, -4, 2, 11, -10, -6, 6}},
        // Test Case 54
        {11, {-5, 0, 12, 13, 14, -9, -14, 1, 15, 10, -1, -8},
                9, {-1, -6, 11, 4, 8, 1, 0, 6, 9, 11}},
        // Test Case 55
        {10, {-1, -3, 12, 11, -8, -14, 6, -7, 1, -13, -8},
                8, {14, 11, 2, -12, 11, -9, 4, 0, -4}},
        // Test Case 56
        {3, {14, 9, -14, -6},
                3, {-6, -2, -13, -11}},
        // Test Case 57
        {8, {10, 1, -10, 7, 9, -2, 4, -13, -11},
                10, {-3, 0, -5, -14, -9, 11, -6, 14, -4, -3, 5}},
        // Test Case 58
        {10, {-8, -2, 5, 12, -9, -3, 6, -6, 1, 5, -7},
                10, {-8, -10, 8, -11, 11, -13, -3, -6, 7, 9, 11}},
        // Test Case 59
        {2, {-4, -9, 4},
                7, {6, 12, -9, -13, 10, 9, -3, 9}},
        // Test Case 60
        {6, {15, -13, 0, -10, -2, -9, -14},
                0, {6}},
        // Test Case 61
        {4, {13, -13, 3, 2, 2},
                6, {7, 2, -6, -12, -3, -5, 8}},
        // Test Case 62
        {2, {1, 10, -7},
                9, {7, -1, -12, -9, -2, 8, 7, -8, -4, -10}},
        // Test Case 63
        {4, {10, 4, -1, -8, -14, 0},
                2, {0, -13, 9}},
        // Test Case 64
        {0, {2},
                0, {12}},
        // Test Case 65
        {5, {-14, -1, 6, 7, -2, 14},
                3, {-3, -14, 7, -13}},
        // Test Case 66
        {4, {-14, 6, 2, 15, 15},
                0, {14}},
        // Test Case 67
        {1, {9, -7},
                1, {7, 1}},
        // Test Case 68
        {5, {-14, -6, -13, 1, 11, -7},
                10, {11, 4, 7, 14, 15, -9, -11, 5, 5, 7, 11}},
        // Test Case 69
        {6, {12, -2, -9, 0, 1, -1, -9},
                7, {8, -9, 8, -13, 15, 10, -14, -5}},
        // Test Case 70
        {10, {-5, 7, -1, 0, -9, 8, 6, 10, 11, -5, -11},
                9, {-2, 3, 2, 14, 2, -11, -12, 14, -3, -13}},
        // Test Case 71
        {11, {8, 8, 3, -8, -13, -3, 3, 8, 0, -11, -9, 6},
                11, {1, -4, -5, -7, -8, -5, -5, -1, -14, -10, 6, 12}},
        // Test Case 72
        {8 , {4, -9, 10, -14, 5, -4, -12, -3, 1},
                0, {15}},
        // Test Case 73
        {11, {-7, 14, 0, 15, 14, 8, -3, -10, 4, 1, 15, 4},
                1, {7, -2}},
        // Test Case 74
        {5, {-9, 1, 0, -9, -13, -3},
                6, {1, 6, 2, -6, 12, 1, -1}},
        // Test Case 75
        {11, {1, -3, -7, -11, -11, 0, 10, -14, -5, -12, 0, 9},
                0, {-9}},
        // Test Case 76
        {5, {-11, -6, 8, 2, 6, -5},
                10, {-8, -10, -9, -14, -14, -6, 5, 13, 14, 9, -5}},
        // Test Case 77
        {2, {8, 4, -14},
                11, {6, -8, -13, 13, 6, 2, -2, -12, 0, 6, -9, 5}},
        // Test Case 78
        {3, {13, -1, -1, -13},
                3, {-1, -7, 6, -7}},
        // Test Case 79
        {3, {10, -7, 6, -7},
                10, {-12, -1, 14, -6, -12, 15, 1, -2, 4, -11, -8}},
        // Test Case 80
        {4, {-14, 10, 0, -9, -2},
                11, {3, 15, 1, -1, 9, 3, 10, 15, -10, -9, 14, 7}},
        // Test Case 81
        {0, {11},
                0, {-14}},
        // Test Case 82
        {2, {5, 1, -1},
                9, {-10, -11, 7, 3, 0, -2, 6, -6, -14, -1}},
        // Test Case 83
        {6, {-12, 7, -5, -9, -7, 6, 2},
                10, {5, -14, -1, -7, -5, -11, 12, 2, 11, -1, 3}},
        // Test Case 84
        {11, {-13, -5, 0, -10, 12, -11, -1, -11, -4, -9, 2, -8},
                7, {5, -6, 13, -13, 10, 9, 0, -3}},
        // Test Case 85
        {6, {-9, 3, 10, -9, 7, -2, 14},
                9, {8, 15, -14, -12, -6, 5, -10, -13, 1, -7}},
        // Test Case 86
        {0, {15},
                1, {-12, -8}},
        // Test Case 87
        {10, {-14, 1, 15, -9, 12, 14, 8, 5, 15, -3, 1},
                5, {-5, 14, 7, 4, 13, -8}},
        // Test Case 88
        {5, {10, 8, 4, 13, 0, 3},
                9, {12, 11, -9, 11, 11, 15, 13, -13, -2, 15}},
        // Test Case 89
        {8, {-14, -1, 2, 8, -12, -12, 15, 9, 5},
                5, {-9, -4, -14, -1, 9, 13}},
        // Test Case 90
        {6, {-3, -4, 11, -9, -10, 5, -9},
                2 , {-13, -6, -5}},
        // Test Case 91
        {1, {-14, -6},
                8, {5, 1, 11, 7, -13, 6, 6, 15, -3}},
        // Test Case 92
        {8, {11, -5, 14, -8, -1, 6, 0, 12, -14},
                7, {-3, 7, 2, 12, -6, -9, 14, 8}},
        // Test Case 93
        {7, {3, -12, 13, 11, -11, 2, -5, -14},
                3, {-6, 9, -6, 11}},
        // Test Case 94
        {4, {-8, 2, -10, -8, -2},
                2, {-8, -11, -3}},
        // Test Case 95
        {10, {1, 1, 7, -9, 7, -9, -9, -12, 14, -14, -10},
                4, {1, -3, 12, -2, -5, 0}},
        // Test Case 96
        {7, {-13, 3, -5, -13, 10, -6, -5, 12},
                10, {-4, 8, -12, 0, 14, 2, 10, 11, 1, -9, 12}},
        // Test Case 97
        {6, {-4, 13, -6, 5, -7, 10, 2},
                7, {5, 2, 9, 14, -13, -10, -14, 12}},
        // Test Case 98
        {9, {-11, 10, 15, 4, 3, 14, -1, 1, 5, 5},
                2, {15, -10, -12}},
        // Test Case 99
        {8, {5, -9, 14, 2, -12, -4, 13, 1, 14},
                5, {0, -14, -9, -11, 14, -1}},
        // Test Case 100
        {4, {12, 6, -4, -8, -8},
                5, {3, 10, 0, 4, -2, -2}}
};



int main() {

    std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    for (int i=0; i < 100; i++){
        int degree1 = arr[i].degree1;
        vector<double> coeffs1 = arr[i].coeffs1;
        int degree2 = arr[i].degree2;
        vector<double> coeffs2 = arr[i].coeffs2;

        cout << "Test Case " << i+1 << endl;
        Polynomial p1(coeffs1); // Represents the first polynomial
        Polynomial p2(coeffs2); // Represents the second polynomial
        Polynomial sum = p1 + p2;
        Polynomial difference = p1 - p2;
        Polynomial product = p1 * p2;

        cout << "p1: " << p1 << endl;
        cout << "p2: " << p2 << endl;
        cout << "p1 + p2: " << sum << endl;
        cout << "p1 - p2: " << difference << endl;
        cout << "p1 * p2: " << product << endl << endl;

        double x = 2.5;
        cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
        cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl << endl;

        cout << "Derivative of p1: " << p1.derivative() << endl;
        cout << "Derivative of p2: " << p2.derivative() << endl << endl;

        cout << "Integral of p1: " << p1.integral() << endl;
        cout << "Integral of p2: " << p2.integral() << endl << endl;

        cout << "Definite integral of p1 from 0 to 1: " << p1.integral(0, 1) << endl;
        cout << "Definite integral of p2 from 0 to 1: " << p2.integral(0, 1) << endl << endl;

    }

    std::cout.rdbuf(coutbuf); //reset to standard output again
    out.close();

    return 0;
}