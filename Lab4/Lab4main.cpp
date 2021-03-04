/*
NAME: Ashish Kumar
ASSIGNMENT: Lab 4
SOURCES: Prim's algorithm from the book
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>


using namespace std;


vector<int> get_user_input();
vector< vector<int> > get_processed_wam(vector<int> user_inp);
void display_adj_matrix(vector< vector<int> > wam, string text);
vector< vector<int> > get_min_span_tree_prim(vector< vector<int> > wam);
vector< vector<int> > initialize_matrix(unsigned int size);
int get_sum_of_values(vector< vector<int> > mat);


int main() {
    /* main function */

    vector< vector<int> > wam;
    vector< vector<int> > prim_out;
    vector<int> user_inp;
    int graph_weight;
    
    cout << endl << "Student Name: Ashish Kumar" << endl;

    user_inp = get_user_input();
    wam = get_processed_wam(user_inp);
    display_adj_matrix(wam, "The WAM entered is:");
    prim_out = get_min_span_tree_prim(wam);
    display_adj_matrix(prim_out, "\nThe output from Prim's algorithm is:");
    graph_weight = get_sum_of_values(prim_out);

    cout << "The total weight of the graph is " << graph_weight << endl << endl;
    
    return 0;
}


vector<int> get_user_input() {
    /*
    Gets input from the user.

    Args:
        None
    
    Returns:
        The user inputs representing the adjacency matrix
    */
    vector<int> nums;
    int a;

    cout << endl << "Enter the WAM please " << endl << endl;

    while (cin >> a) {
        nums.push_back(a);
    }

    return nums;
}


vector< vector<int> > get_processed_wam(vector<int> user_inp) {
    /*
    Helps convert an array of user inputs into a 2D matrix of vector ints.  This
    has been done to make the program readable in a way that i, j th values in
    the 2D array represent the i, j th value in the matrix.

    Args:
        An array of user inputs

    Returns:
        A 2D array representing the adjacency matrix 
    */
    vector< vector<int> > wam;
    vector<int> temp_wam;
    vector<int>::iterator iterator = user_inp.begin();

    for (int i = 0; i < sqrt(user_inp.size()); ++i) {
        for (int j = 0; j < sqrt(user_inp.size()); ++j) {
            temp_wam.push_back(*iterator);
            ++iterator;
        }
        wam.push_back(temp_wam);
        temp_wam.clear();
    }

    return wam;
}


void display_adj_matrix(vector< vector<int> > wam, string text) {
    /*
    Displays a 2D matrix on screen along with a text message from the user
    provided through the variable 'text'

    Args:
        wam: A 2D array representing the adjacency matrix
        text: A display string to be displayed along with the matrix

    Returns:
        None
    */
    cout << text << endl;
    for (unsigned int i = 0; i < wam.size(); ++i) {
        for (unsigned int j = 0; j < wam.size(); ++j) {
            cout << wam[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}


vector< vector<int> > get_min_span_tree_prim(vector< vector<int> > wam) {
    /*
    Computes the minimum spanning tree for the weighted adjacency matrix using
    the Prim's algorithm

    Args:
        wam: Weighted Adjacency Matrix
    
    Returns:
        The output of the Prim's algorithm i.e. the minimum spanning tree
        corresponding to 'wam'
    */
    vector< vector<int> > prim_out = initialize_matrix(wam.size());
    vector<bool> V;
    unsigned int i, j, k, min_ptr_j, min_ptr_k;
    int min;

    V.push_back(true);
    for (i = 1; i < wam.size(); ++i){
        V.push_back(false);
    }

    for (i = 1; i < wam.size(); ++i){
        min = INT32_MAX;
        for (j = 0; j < V.size(); ++j) {
            if (V[j]) {
                for (k = 0; k < wam[j].size(); ++k) {
                    if ((!V[k]) && (wam[j][k] != 0) && (wam[j][k] < min)) {
                        min = wam[j][k];
                        min_ptr_k = k;
                        min_ptr_j = j;
                    }
                }
            }
        }
        prim_out[min_ptr_j][min_ptr_k] = wam[min_ptr_j][min_ptr_k];
        prim_out[min_ptr_k][min_ptr_j] = wam[min_ptr_k][min_ptr_j];
        V[min_ptr_k] = true;
    }

    return prim_out;
}


vector< vector<int> > initialize_matrix(unsigned int size) {
    /*
    Initialize an n x n 2D array with a zero value

    Args:
        size: Size of the 2D array

    Returns:
        A 2D array with values initialized to zero
    */
    vector< vector<int> > mat;
    vector<int> mat_temp;

    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            mat_temp.push_back(0);
        }
        mat.push_back(mat_temp);
        mat_temp.clear();
    }

    return mat;
}


int get_sum_of_values(vector< vector<int> > mat) {
    /*
    Function to compute the total weight of a graph represented by an adjacency
    matrix.

    Args:
        mat: An adjacency matrix

    Returns:
        Weight of the graph
    */
    int sum = 0;

    for (unsigned int i = 0; i < mat.size(); ++i) {
        for (unsigned int j = 0; j < mat.size(); ++j) {
            sum += mat[i][j];
        }
    }

    return (sum/2);
}
