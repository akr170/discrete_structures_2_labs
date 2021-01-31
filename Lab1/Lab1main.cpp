#include <iostream>
#include <string>
#include <cmath>


using namespace std;


#define MAXARRAYSIZE 625


class cs251set {
private:
    string setA[MAXARRAYSIZE];
    unsigned int num_elements;
    void insert(string value);
    string get_value_at(unsigned int i);

public:
    cs251set();
    void insert_values(string unpro_set);
    unsigned int size();
    string displayset(string set_name="");
    bool contains(string elem);
    cs251set intersection(cs251set setB);
    cs251set setunion(cs251set setB);
    cs251set minus(cs251set setB);
    cs251set cross(cs251set setB);
};


cs251set get_user_input(string setname);
void disp_cardinality_roster(cs251set a_set, string text1, string text2);
void disp_pwr_set_cardinality(cs251set a_set, string text2);


int main() {
    cs251set setA, setB;
    cs251set A_int_B, A_union_B, A_minus_B, B_minus_A, A_cross_B;

    cout << endl << "Student Name: Ashish Kumar" << endl << endl;

    setA = get_user_input("A");
    setB = get_user_input("B");

    A_int_B = setA.intersection(setB);
    A_union_B = setA.setunion(setB);
    A_minus_B = setA.minus(setB);
    B_minus_A = setB.minus(setA);
    A_cross_B = setA.cross(setB);

    disp_cardinality_roster(A_int_B, "A intersect B = ", "of the intersection ");
    disp_cardinality_roster(A_union_B, "A U B = ", "of the union ");
    disp_cardinality_roster(A_minus_B, "A - B = ", "");
    disp_cardinality_roster(B_minus_A, "B - A = ", "");
    disp_cardinality_roster(A_cross_B, "A X B = ", "of A X B ");
    disp_pwr_set_cardinality(A_cross_B, "of the cross product ");

    return 0;
}


void cs251set::insert(string value) {
    /*
    Aids in iserting a single string value in the setA array of class cs251set
    
    Args:
        value: a single string value
    
    Returns:
        Nothing
    
    Throws:
        Error if num of elements in set exceed the maximum allowed
    */
    bool add_element = true;

    if (num_elements >= MAXARRAYSIZE) {
        cout << "Error occurred while inserting value: " << value << endl;
        cout << "Set full.  Cannot insert more elements." << endl;
        throw;
    }

    if (value == "") add_element = false;

    for (unsigned int i = 0; i < num_elements; ++i) {
        if (setA[i] == value) add_element = false;
    }
    if (add_element) {
        setA[num_elements] = value;
        ++num_elements;
    }
}


string cs251set::get_value_at(unsigned i) {
    /*
    Helper function to get i-th element from the set array.

    Args:
        i: the index
    
    Returns:
        A string value
    
    Throws:
        Error if i is greater than the number of elements in the set
    */
    if (i < 0) {
        cout << "Set index cannot be negative" << endl;
        throw;
    } else if (i < num_elements) {
        return setA[i];
    } else {
        cout << "Trying to retrieve element " << i << " from the set that ";
        cout << "only contains " << num_elements << " elements" << endl;
        throw;
    }
}


cs251set::cs251set() {
    /*
    Class constructor
    */
    num_elements = 0;
}


void cs251set::insert_values(string unpro_set) {
    /*
    Takes in a string and splits it by space character.  Inserts the resulting
    string values after split into the set class using private insert function.

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
    int str_b, i = 0;
    string subs;
    str_b = i;
    
    while (( unpro_set[i] != '\0' ) && ( num_elements < MAXARRAYSIZE )){
        if ( unpro_set[i] == ' ' ) {
            subs = unpro_set.substr(str_b, (i - str_b));
            insert(subs);
            str_b = i + 1;
        }
        ++i;
    }

    if ( unpro_set[i] == '\0' ) {
        subs = unpro_set.substr(str_b, (i - str_b));
        insert(subs);
    } else {
        cout << "Number of elements in set exceed 25" << endl;
        throw;
    }

}


unsigned int cs251set::size() {
    /*
    Class method to return the number of elements contained in the set

    Args:
        None
    
    Returns:
        Number of elements contained within the set
    */
    return num_elements;
}


string cs251set::displayset(string set_name) {
    /*
    Iterates over set elements and generates a nicely formatted string that can
    be displayed on screen.

    Args:
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
    string disp_str = set_name + "{ ";

    for (unsigned int i = 0; i < num_elements; ++i) {
        disp_str += setA[i] + ", ";
        flag = true;
    }

    if ( flag ) disp_str = disp_str.substr(0, disp_str.length() - 2);
    disp_str += " }";

    return disp_str;
}


bool cs251set::contains(string elem){
    /*
    Takes in a string input, iterates over the set elements to check if the
    string input exists in the set.

    Args:
        elem: A string input
    
    Returns:
        true if elem exists in the set, false otherwise
    */
    bool flag = false;

    for (unsigned int i = 0; i < num_elements; ++i) {
        if (setA[i] == elem) {
            flag = true;
            break;
        }
    }

    return flag;
}


cs251set cs251set::intersection(cs251set setB) {
    /*
    Function that finds the intersection of two sets.

    The function iterates over the elements of one set and tries to figure out
    if elements are present in the other set.  If an element from one set
    happens to be present in the other set, it is added to a new set called
    "A_intersect_B".

    Args:
        setB: A cs251set object defined above
    
    Returns:
        A cs251set object that contains the elements that are common in both
        setA and setB.
    */
    cs251set A_intersect_B;

    for (unsigned int i = 0; i < num_elements; ++i) {
        if (setB.contains(setA[i])) {
            A_intersect_B.insert(setA[i]);
        }
    }

    return A_intersect_B;
}


cs251set cs251set::setunion(cs251set setB) {
    /*
    Function that finds the union of two sets.

    The function first adds all the elements of setA to a new set called
    A_union_B. It then iterates over the elements of setB to figure out if those
    elements are present in the union set. If an element from setB is not
    present in the union set then this function adds that particular element to
    the union set.

    Args:
        setB: A cs251set object
    
    Returns:
        A cs251set object that contains the elements that are a union of setA
        and setB.
    */
    cs251set A_union_B;

    for (unsigned int i = 0; i < num_elements; ++i) {
        A_union_B.insert(setA[i]);
    }

    for (unsigned int i = 0; i < setB.size(); ++i) {
        A_union_B.insert(setB.get_value_at(i));
    }

    return A_union_B;
}


cs251set cs251set::minus(cs251set setB) {
    /*
    Function that calculates the relative complement of A and B.

    The function iterates over the elements of setA and figures out if those
    exist in setB.  The elements from setA that do not exist in setB are added
    into a new set called "A_minus_B".

    Args:
        setB: A cs251set object
    
    Returns:
        A cs251set object that contains the elements that represent setA - setB.
    */
    cs251set A_minus_B;

    for (unsigned int i = 0; i < num_elements; ++i) {
        if (not(setB.contains(setA[i]))) {
            A_minus_B.insert(setA[i]);
        }
    }

    return A_minus_B;
}


cs251set cs251set::cross(cs251set setB) {
    /*
    Function that computes the ordered pairs that represent the cross product of
    two sets.

    The function iterates over the elements of both setA and setB and adds
    ordered pairs of their elemets into a new set called "A_cross_B".

    Args:
        setB: A cs251set object
    
    Returns:
        A cs251set object that contains ordered pairs from the cross product of
        setA and setB.
    */
    cs251set A_cross_B;
    string pair;

    for (unsigned int i = 0; i < num_elements; ++i) {
        for (unsigned int j = 0; j < setB.size(); ++j) {
            pair = "(" + setA[i] + ", " + setB.get_value_at(j) + ")";
            A_cross_B.insert(pair);
        }
    }

    return A_cross_B;
}


cs251set get_user_input(string set_name) {
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
    cs251set setA;

    cout << endl;
    cout << "Input the items in set " << set_name << ", separated by spaces: ";
    getline(std::cin, setA_unpro);
    setA.insert_values(setA_unpro);
    cout << endl;
    cout << "The following is a list of the items in set " << set_name << ".  ";
    cout << set_name << " contains " << setA.size() << " items." << endl;
    cout << setA.displayset(set_name + " = ") << endl << endl;

    return setA;
}


void disp_cardinality_roster(cs251set a_set, string text1, string text2) {
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
    cout << a_set.displayset(text1) << endl;
    cout << "The cardinality " << text2 << "is " << a_set.size() << endl;
    cout << endl;
}


void disp_pwr_set_cardinality(cs251set a_set, string text2) {
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
