/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 5
SOURCES:    Horner's algo from the book
            https://levelup.gitconnected.com/ (tutorial on chrono)
*/

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>


using namespace std;


vector<unsigned int> generate_coefficients(unsigned int n);
string generate_polynomial(vector<unsigned int> coeff);
long double compute_value_usual(unsigned int n, long double x,
                                vector<unsigned int> coeff);
long double compute_value_horner(unsigned int n, long double x,
                                 vector<unsigned int> coeff);


int main() {
    /* main function */

    vector<unsigned int> coeff;
    long double x, px_horner, px_usual;
    string poly;
    chrono::high_resolution_clock::time_point begin;
    chrono::duration<double> elapsed_horner, elapsed_usual;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<long double> distribution(-20.0, 20.0);

    cout << endl << "Student Name: Ashish Kumar" << endl;

    for(unsigned int n = 1; n <= 20; ++n) {
        coeff = generate_coefficients(n);
        x = distribution(generator);
        poly = generate_polynomial(coeff);

        begin = chrono::high_resolution_clock::now();
        px_horner = compute_value_horner(n, x, coeff);
        elapsed_horner = (chrono::high_resolution_clock::now() - begin);

        begin = chrono::high_resolution_clock::now();
        px_usual = compute_value_usual(n, x, coeff);
        elapsed_usual = (chrono::high_resolution_clock::now() - begin);
        
        cout << endl;
        cout << "degree " << n << endl;
        cout << "\t" << poly << endl;
        cout << "\tx = " << x << endl;
        cout << "\tHorner " << elapsed_horner.count() << "seconds." << endl;
        cout << "\tP(x) = " << px_horner << endl;
        cout << "\tNot Horner " << elapsed_usual.count() << "seconds." << endl;
        cout << "\tP(x) = " << px_usual << endl << endl;
    }
    return 0;
}


vector<unsigned int> generate_coefficients(unsigned int n) {
    /*
    Generates n random coefficients between 1 and 99

    Args:
        n: the number of coefficients that need to be generated

    Returns:
        A vector of n random coefficients between 1 and 99
    */
    vector<unsigned int> coeff;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 99);

    for(unsigned int i = 0; i <= n; ++i) {
        coeff.push_back(distribution(generator));
    }

    return coeff;
}

string generate_polynomial(vector<unsigned int> coeff) {
    /*
    Generates a string of the polynomial for display purposes.

    Args:
        coeff: An array of coefficients
    
    Returns:
        A string representing the polynomial in the following format
            a[n]*x^n + a[n - 1]*x^(n-1) + ... + a[2]*x^2 + a[1]*x + a[0]
    */
    string poly = "";

    for(unsigned int i = 0; i < coeff.size(); ++i) {
        poly = " + " + to_string(coeff[i]) + "x^" + to_string(i) + poly;
    }

    poly = poly.substr(3, poly.size() - 3);

    return poly;
}


long double compute_value_usual(unsigned int n, long double x,
                                vector<unsigned int> coeff) {
    /*
    Computes the value of the polynomial of the format
        a[n]*x^n + a[n - 1]*x^(n-1) + ... + a[2]*x^2 + a[1]*x + a[0]
    in a normal way through multiplication to compute the nth term a[n]*x^n and
    then adding the result of each individual term into a sum variable.

    Args:
        n: degree of the polynomial
        x: value of the dependent variable
        coeff: an array of coefficients

    Returns:
        the computed value of the polynomial for a given x
    */
    long double px = coeff[0];
    long double runn_mult = 1;

    for(unsigned int i = 1; i <= n; ++i) {
        runn_mult = runn_mult * x;
        px += runn_mult * coeff[i];
    }

    return px;
}


long double compute_value_horner(unsigned int n, long double x,
                                 vector<unsigned int> coeff) {
    /*
    Computes the value of the polynomial of the format
        a[n]*x^n + a[n - 1]*x^(n-1) + ... + a[2]*x^2 + a[1]*x + a[0]
    using Horner's rule.

    Args:
        n: degree of the polynomial
        x: value of the dependent variable
        coeff: an array of coefficients

    Returns:
        the computed value of the polynomial for a given x
    */
    long double px = coeff[n];

    for(unsigned int i = 1; i <= n; ++i) {
        px = px * x + coeff[n - i];
    }

    return px;
}
