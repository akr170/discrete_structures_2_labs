/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 2
SOURCES: None
*/

#include <iostream>
#include <string>
#include <cmath>


using namespace std;


#define MAXITR 4


long long int calculate_mod(long long int & base, long long int & n,
                            long long int & modulus);
unsigned int determine_max_exponent(long long int & n);


int main() {
    long long int base, n, modulus, residue;

    cout << endl << "Student Name: Ashish Kumar" << endl << endl;

    cout << "This program will calculate a^n mod p." << endl << endl;
    for (int i = 0; i < MAXITR; ++i) {
        cout << "Enter base (a): ";
        cin >> base;
        cout << "Enter exponent (n): ";
        cin >> n;
        cout << "Enter modulus (p): ";
        cin >> modulus;
        
        residue = calculate_mod(base, n, modulus);

        cout << endl;
        cout << "\t";
        cout << base << "^" << n << " mod " << modulus << " = " << residue;
        cout << endl << endl;
    } 

    return 0;
}


long long int calculate_mod(long long int & base, long long int & n,
                            long long int & modulus) {
    /*
    Function that computes the modulus as outlined in the Lab 2 Notes on d2l.

    Args:
        base: base 'a' in the formula a^n mod p
        n: exponent in the formula a^n mod p
        modulus: modulus 'p' in the formula a^n mod p
    
    Returns:
        The result of the formual a^n mod p
    */
    unsigned int max_2_exp;
    long long int temp, residue, running_multiplier = 1;
    bool flag;

    max_2_exp = determine_max_exponent(n);
    temp = n; // copy n in a temp variable so it is not lost during right shift

    for (unsigned int i = 0; i <= max_2_exp; ++i) {
        if (i == 0) {
            residue = base % modulus;
        } else {
            residue = (residue * residue) % modulus;
        }
        flag = temp & 0x01;
        if (flag) {
            running_multiplier = (running_multiplier*residue) % modulus;
        }
        temp = temp >> 1;
    }
    
    return running_multiplier;
}


unsigned int determine_max_exponent(long long int & n) {
    /*
    Function that first helps determine the maximum exponent of 2 that will need
    to be calculated.  This step helps to determine the maximum iteration to
    which the program would need to run.
    
    Notes:
        This function has been implemented to boost the overall efficiency of
        the program.  This function is not critical to achieve the objectives
        of this program.
    
    Args:
        n: the exponent in a^n mod p
    
    Returns:
        The highest power of 2 that would need to be calculated
    */
    long long int temp;
    unsigned int max_2_exp;
    bool flag;

    temp = n; // copy n in a temp variable so it is not lost during right shift

    for (unsigned int i = 0; i < 8*sizeof(n); ++i) {
        flag = temp & 0x01;
        if (flag) {
            max_2_exp = i;
        }
        temp = temp >> 1;
    }

    return max_2_exp;
}
