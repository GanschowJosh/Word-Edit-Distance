/*
Levenshtein distance calculator using the Wagner-Fischer algorithm
*/




#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
using namespace std;

//unused, testing purposes
void printMatrix(vector<vector<int>>& vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << setw(3) << vec[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

//algo
int wagnerFischer(string a, string b) {


    //creating a matrix with dimensions of the length of the strings(plus extra one for empty character at front)
    vector<vector<int>> matrix(a.size() + 1, vector<int>(b.size() + 1));

    //initialize the matrix
    for(size_t i = 0; i <= a.size(); i++) {
        matrix[i][0] = i;
    }
    for(size_t j = 0; j <= b.size(); j++) {
        matrix[0][j] = j;
    }

    for(int i = 1; i <= a.size(); i++) {
        for(int j = 1; j <= b.size(); j++) {
            int subsitutionCost = (a[i-1] == b[j-1]) ? 0 : 1;
            matrix[i][j] = min({matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + subsitutionCost});
        }
    }
    
    return matrix[a.size()][b.size()];
}



int main() {
    string word1;
    string word2;

    cout << "Enter word 1: ";
    cin >> word1;
    cout << "Enter word 2: ";
    cin >> word2;
    cout << "Levenshtein distance is: " << wagnerFischer(word1, word2) << endl;
    return 0;
}