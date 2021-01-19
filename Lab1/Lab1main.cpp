/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 1
SOURCES: None
*/

#include <iostream>
#include <string>
#include <cmath>
#include <set>


using namespace std;


set<string> get_user_input(string setname);
set<string> str_2_set(string & unpro_set);
string set_2_str(set<string> & a_set, string set_name);
set<string> get_A_intersect_B(set<string> & setA, set<string> & setB);
set<string> get_A_union_B(set<string> & setA, set<string> & setB);
set<string> get_A_minus_B(set<string> & setA, set<string> & setB);
set<string> get_A_cross_B(set<string> & setA, set<string> & setB);
void disp_cardinality_roster(set<string> & a_set, string text1, string text2);
void disp_pwr_set_cardinality(set<string> & a_set, string text2);


int main() {
    set<string> setA, setB;
    set<string> A_int_B, A_union_B, A_minus_B, B_minus_A, A_cross_B;

    cout << endl << "Student Name: Ashish Kumar" << endl << endl;

    setA = get_user_input("A");
    setB = get_user_input("B");

    A_int_B = get_A_intersect_B(setA, setB);
    A_union_B = get_A_union_B(setA, setB);
    A_minus_B = get_A_minus_B(setA, setB);
    B_minus_A = get_A_minus_B(setB, setA);
    A_cross_B = get_A_cross_B(setA, setB);

    disp_cardinality_roster(A_int_B, "A intersect B", "of the intersection ");
    disp_cardinality_roster(A_union_B, "A U B", "of the union ");
    disp_cardinality_roster(A_minus_B, "A - B", "");
    disp_cardinality_roster(B_minus_A, "B - A", "");
    disp_cardinality_roster(A_cross_B, "A X B", "of A X B ");
    disp_pwr_set_cardinality(A_cross_B, "of the cross product ");

    return 0;
}


set<string> str_2_set(string & unpro_set) {
    /*
    Takes in the user input in form of a string and splits it by space character

    Notes:
        - If the user provided string is
            "  string1 string2 string3   string4    string5     "
          the set this function will return is
            {"string1", "string2", "string3", "string4", "string5"}
        - Any extra spaces gets removed from the set
    
    Args:
        unpro_set: An space delimited unprocessed str set inputted by the user
    
    Returns:
        pro_set: {"The", "processed", "set", "of", "strings"}
    */
    set<string> pro_set;
    int str_b, i = 0;
    string subs;
    str_b = i;
    
    while ( unpro_set[i] != '\0' ) {
        if ( unpro_set[i] == ' ' ) {
            subs = unpro_set.substr(str_b, (i - str_b));
            pro_set.insert(subs);
            str_b = i + 1;
        }
        ++i;
    }
    subs = unpro_set.substr(str_b, (i - str_b));
    pro_set.insert(subs);

    // cleaning up any empty ("") elements due to repeated spaces
    set<string>::iterator it = pro_set.find("");
    if ( it != pro_set.end() ) {
        pro_set.erase(it);
    }

    return pro_set;
}


set<string> get_user_input(string set_name) {
    /*
    A helper function that inputs and processes user provided strings.

    Notes:
        The space delimited user provided strings are read in and temporarily
        stored in the variable "setA_unpro".

    Args:
        set_name: The name of the set that is displayed in the output.
    
    Returns:
        setA: {"The", "processed", "set", "of", "strings"}
    */
    string setA_unpro;
    set<string> setA;

    cout << endl;
    cout << "Input the items in set " << set_name << ", separated by spaces: ";
    getline(std::cin, setA_unpro);
    setA = str_2_set(setA_unpro);
    cout << endl;
    cout << "The following is a list of the items in set " << set_name << ".  ";
    cout << set_name << " contains " << setA.size() << " items." << endl;
    cout << set_2_str(setA, set_name) << endl << endl;

    return setA;
}


string set_2_str(set<string> & a_set, string set_name) {
    /*
    Takes in a set of strings and converts it to a nicely formatted string that
    can be displayed on screen.

    Args:
        a_set: A C++ set object
        set_name: The name of the set that is appended to the string so it could
            be displayed properly on the screen
    
    Returns:
        A string representing the set.

    Notes:
        If a_set is {"string1", "string2", "string3"}, and the set_name is "AxB"
        then the string that is returned is
            "AxB = { string1, string2, string3 }"
    */
    bool flag = false;
    string disp_str = set_name + " = { ";

    for (set<string>::iterator i = a_set.begin(); i != a_set.end(); i++) {
        disp_str += *i + ", ";
        flag = true;
    }

    if ( flag ) disp_str = disp_str.substr(0, disp_str.length() - 2);
    disp_str += " }";

    return disp_str;
}


set<string> get_A_intersect_B(set<string> & setA, set<string> & setB) {
    /*
    Function that finds the intersection of two sets.

    The function iterates over the elements of one set and tries to figure out
    if elements are present in the other set.  If an element from one set
    happens to be present in the other set, it is added to a new set called
    "A_intersect_B".

    Args:
        setA: A C++ set object
        setB: A C++ set object
    
    Returns:
        A C++ set object that contains the elements that are common in both
        setA and setB.
    */
    set<string> A_intersect_B;

    for (set<string>::iterator i = setA.begin(); i != setA.end(); i++) {
        set<string>::iterator j = setB.find(*i);
        if ( j != setB.end() ) {
            A_intersect_B.insert(*i);
        }
    }

    return A_intersect_B;
}


set<string> get_A_union_B(set<string> & setA, set<string> & setB) {
    /*
    Function that finds the union of two sets.

    The function first adds all the elements of setA to a new set called
    A_union_B. It then iterates over the elements of setB to figure out if those
    elements are present in the union set. If an element from setB is not
    present in the union set then this function adds that particular element to
    the union set.

    Args:
        setA: A C++ set object
        setB: A C++ set object
    
    Returns:
        A C++ set object that contains the elements that are a union of setA and
        setB.
    */
    set<string> A_union_B;

    for (set<string>::iterator i = setA.begin(); i != setA.end(); i++) {
        A_union_B.insert(*i);
    }

    for (set<string>::iterator i = setB.begin(); i != setB.end(); i++) {
        set<string>::iterator j = A_union_B.find(*i);
        if ( j == A_union_B.end() ) {
            A_union_B.insert(*i);
        }
    }

    return A_union_B;
}


set<string> get_A_minus_B(set<string> & setA, set<string> & setB) {
    /*
    Function that calculates the relative complement of A and B.

    The function iterates over the elements of setA and figures out if those
    exist in setB.  The elements from setA that do not exist in setB are added
    into a new set called "A_minus_B".

    Args:
        setA: A C++ set object
        setB: A C++ set object
    
    Returns:
        A C++ set object that contains the elements that represent setA - setB.
    */
    set<string> A_minus_B;

    for (set<string>::iterator i = setA.begin(); i != setA.end(); i++) {
        set<string>::iterator j = setB.find(*i);
        if ( j == setB.end() ) {
            A_minus_B.insert(*i);
        }
    }

    return A_minus_B;
}


set<string> get_A_cross_B(set<string> & setA, set<string> & setB) {
    /*
    Function that computes the ordered pairs that represent the cross product of
    two sets.

    The function iterates over the elements of both setA and setB and adds
    ordered pairs of their elemets into a new set called "A_cross_B".

    Args:
        setA: A C++ set object
        setB: A C++ set object
    
    Returns:
        A C++ set object that contains ordered pairs from the cross product of
        setA and setB.
    */
    set<string> A_cross_B;

    for (set<string>::iterator i = setA.begin(); i != setA.end(); i++) {
        for (set<string>::iterator j = setB.begin(); j != setB.end(); j++) {
            A_cross_B.insert("(" + *i + ", " + *j + ")");
        }
    }

    return A_cross_B;
}


void disp_cardinality_roster(set<string> & a_set, string text1, string text2) {
    /*
    Helper function that displays the roster and the cardinality of a set.

    Args:
        a_set: a C++ set object
        text1: the name of the set that is displayed with the set roster
        text2: an additional optional piece of text that is displayed on screen

    Returns:
        None
    */
    cout << endl;
    cout << set_2_str(a_set, text1) << endl;
    cout << "The cardinality " << text2 << "is " << a_set.size() << endl;
    cout << endl;
}


void disp_pwr_set_cardinality(set<string> & a_set, string text2) {
    /*
    Helper function that displays the cardinality of the power set of a set.

    Notes:
        Cardinality of the power set of a set is given by:
            
            cardinality of the power set = 2^N
            
            where N is the number of elements in the original set.

    Args:
        a_set: a C++ set object whose power set's cardinality will be computed
        text2: an additional optional piece of text that is displayed on screen

    Returns:
        None
    */
    cout << endl;
    cout.precision(20);
    cout << "The cardinality of the power set " << text2 << "is ";
    cout << pow(2, a_set.size()) << endl;
    cout << endl;
}
