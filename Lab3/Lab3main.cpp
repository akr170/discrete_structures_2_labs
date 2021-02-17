/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 3
SOURCES: None
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;


#define MAXARRAYSIZE 150


class cs251list {
private:
    long long int encoded_vals[MAXARRAYSIZE];
    long long int decoded_vals[MAXARRAYSIZE];
    long long int pq, d;
    unsigned int num_elements;
    void insert(long long int value);

public:
    cs251list();
    void set_private_key(long long int pq, long long int d);
    void insert_values(string unpro_set);
    unsigned int size();
    string get_msg();
    void decode();
};


long long int calculate_mod(long long int & base, long long int & n,
                            long long int & modulus);
unsigned int determine_max_exponent(long long int & n);
string parse_cipher_filepath(int argc, char **argv);
cs251list get_encoded_values_from_file(string filepath);
long long int get_pq_from_line(string line);
long long int get_d_from_line(string line);


int main(int argc, char **argv) {
    string filepath;
    cs251list ciphers;

    cout << endl << "Student Name: Ashish Kumar" << endl;

    filepath = parse_cipher_filepath(argc, argv);
    ciphers = get_encoded_values_from_file(filepath);
    ciphers.decode();
    cout << ciphers.get_msg() << endl;
    cout << endl;

    return 0;
}


void cs251list::insert(long long int value) {
    /*
    Aids in iserting a single encoded value in the setA array of class cs251list
    
    Args:
        value: a single long long int value
    
    Returns:
        Nothing
    
    Throws:
        Error if num of elements in set exceed the maximum allowed
    */
    if (num_elements >= MAXARRAYSIZE) {
        cout << "Error occurred while inserting value: " << value << endl;
        cout << "List full.  Cannot insert more elements." << endl;
        throw;
    }

    encoded_vals[num_elements] = value;
    ++num_elements;
}


cs251list::cs251list() {
    /*
    Class constructor
    */
    num_elements = 0;
}


void cs251list::set_private_key(long long int product, long long int exp) {
    /*
    Class method that helps set the private keys in the class variables.
    
    Args:
        product: pq
        exp: d
    
    Returns:
        None
    */
    pq = product;
    d = exp;
}


void cs251list::insert_values(string unpro_set) {
    /*
    Takes in a string and splits it by space character.  Inserts the resulting
    string values after split into a string array using private insert function.
    
    Args:
        unpro_set: An space delimited unprocessed str set inputted from file
    
    Returns:
        pro_set: {"The", "processed", "list", "of", "strings"}
    */
    int str_b, i = 0;
    string subs;
    str_b = i;

    while ((unpro_set[i] == ' ') and unpro_set[i] != '\0') {
        ++i;
    }

    while (( unpro_set[i] != '\0' ) && ( num_elements < MAXARRAYSIZE )){
        if ( unpro_set[i] == ' ' ) {
            subs = unpro_set.substr(str_b, (i - str_b));
            insert(stoi(subs));
            str_b = i + 1;
        }
        while ((unpro_set[i] == ' ') and unpro_set[i] != '\0') {
            ++i;
        }
        ++i;
    }

    if ( unpro_set[i] == '\0' ) {
        subs = unpro_set.substr(str_b, (i - str_b));
        insert(stoi(subs));
    } else {
        cout << "Number of elements in set exceed "<< MAXARRAYSIZE << endl;
        throw;
    }
}


unsigned int cs251list::size() {
    /*
    Class method to return the number of elements contained in the list

    Args:
        None
    
    Returns:
        Number of elements contained within the list
    */
    return num_elements;
}


string cs251list::get_msg() {
    /*
    Iterates over array elements of decoded values and generates a message.

    Args:
        None
    
    Returns:
        A string representing the decoded message.
    */
    string disp_str = "";

    for (unsigned int i = 0; i < num_elements; ++i) {
        disp_str.push_back((char)decoded_vals[i]);
    }

    return disp_str;
}


void cs251list::decode() {
    /*
    Decodes an encoded message using the formula M = C^d mod pq
    */
    for (unsigned int i = 0; i < size(); ++i) {
        decoded_vals[i] = calculate_mod(encoded_vals[i], d, pq);
    }
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


string parse_cipher_filepath(int argc, char** argv) {
    /*
    Helper function to parse out a filepath from the user provided args.  The
    filepath is for file that contains the private keys and the encoded messages

    Args:
        argc: number of arguments
        argv: pointer to the array of pointer to the arguments
    
    Returns:
        /path/to/the/file/that/contains/encoded/message
    */
    char* arg_ptr = *argv;
    int i, j;
    string temp, filepath;

    i = 0;
    j = 0;

    if (argc < 2) {
        cout << "Not enough input arguments. ";
        cout << "Please provide cipher filepath." << endl;
        throw;
    }
    else if (argc > 2) {
        cout << "Too many input arguments. Please revise." << endl;
        throw;
    }

    while (j < argc) {
        temp = "";
        while ((arg_ptr[i] != '\0') and (arg_ptr[i] != ' ')) {
            temp.push_back(arg_ptr[i]);
            ++i;
        }
        ++arg_ptr;
        if (j==1) {
            filepath = temp;
        }
        ++j;
    }

    return filepath;
}


cs251list get_encoded_values_from_file(string filepath) {
    /*
    Parser to parse out the private keys and encoded message from the user
    provided file.
    */
    cs251list ciphers;
    string line;
    int pq, d, i = 0;
    ifstream myfile (filepath);

    if (myfile.is_open()) {
        while ( getline (myfile,line) )
        {
            if (i == 0) {
                pq = get_pq_from_line(line);
                d = get_d_from_line(line);
                ciphers.set_private_key(pq, d);
            }
            else {
                ciphers.insert_values(line);
            }
            ++i;
        }
        myfile.close();
    } else {
        cout << "File was not found.  Please revise" << endl << endl;
        throw;
    }

    return ciphers;
}


long long int get_pq_from_line(string line){
    /*
    Helper function to parse out the value of pq
    */
    int bst, num, pq, i = 0;

    while (line[i] != '\0') {
        if (line[i] == '=') break;
        ++i;
    }
    bst = i + 1;
    ++i;
    num = 0;
    while (line[i] != '\0') {
        if (line[i] == 'd') break;
        ++num;
        ++i;
    }

    pq = stoi(line.substr(bst, num));

    return pq;
}


long long int get_d_from_line(string line){
    /*
    Helper function to parse out the value of d
    */
    int bst, num, d, i = 0;

    while (line[i] != '\0') {
        if (line[i] == 'd') break;
        ++i;
    }

    ++i;

    while (line[i] != '\0') {
        if (line[i] == '=') break;
        ++i;
    }
    bst = i + 1;
    ++i;
    num = 0;
    while (line[i] != '\0') {
        ++num;
        ++i;
    }

    d = stoi(line.substr(bst, num));

    return d;
}
