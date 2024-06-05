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

//prints out the steps taken for the edit
void stepPrinter(vector<pair<int, pair<char, char>>>& steps, string word) {
    int count = 1;
    string newWord = word;
    int pos = 0; //position of the operation in the string
    bool print = true;
    for(auto& it : steps) { //iterating over each step
        int op = it.first;
        char lettera = it.second.first;
        char letterb = it.second.second;
        switch(op){
            case 0: //nothing occurred
                pos++;
                break;
            case 1: //substitution occurred
                cout << count << ". ";
                count++;
                cout << "Swap " << lettera << " for " << letterb << endl;
                if(pos < newWord.size()) {
                    newWord[pos++] = letterb;
                }
                cout << "Current word: " << newWord << endl;
                break;
            case 2: //deletion occurred
                cout << count << ". ";
                count++;
                cout << "Delete " << lettera << endl;
                if(pos < newWord.size()) {
                    newWord.erase(newWord.begin() + pos);
                }
                cout << "Current word: " << newWord << endl;
                break;
            case 3: //insertion occurred
                cout << count << ". ";
                count++;
                cout << "Insert " << lettera << endl;
                newWord.insert(newWord.begin() + pos++, lettera);
                cout << "Current word: " << newWord << endl;
                break;
        }
    }
}

//algo
void wagnerFischer(string a, string b) {


    //creating a matrix with dimensions of the length of the strings(plus extra one for empty character at front)
    vector<vector<int>> matrix(a.size() + 1, vector<int>(b.size() + 1));

    //initialize the matrix
    for(size_t i = 0; i <= a.size(); i++) {
        matrix[i][0] = i;
    }
    for(size_t j = 0; j <= b.size(); j++) {
        matrix[0][j] = j;
    }

    //loop to perform operations
    for(int i = 1; i <= a.size(); i++) {
        for(int j = 1; j <= b.size(); j++) {
            int subsitutionCost = (a[i-1] == b[j-1]) ? 0 : 1;
            
            matrix[i][j] = min({matrix[i-1][j] + 1, //deletion
                                matrix[i][j-1] + 1, //insertion
                                matrix[i-1][j-1] + subsitutionCost}); //subsitution
        }
        printMatrix(matrix);
    }

    //loop to backtrack and find steps (favor order: subs, dels, ins)
    vector<pair<int, pair<char, char>>> steps; //vector of pairs: (operation, (letter a, letter b))
    int i = a.size(), j = b.size();
    while(i > 0 && j > 0) {
        int curr = matrix[i][j];
        int sub = matrix[i-1][j-1]; //operation 1
        int del = matrix[i-1][j]; //operation 2
        int ins = matrix[i][j-1]; //operation 3

        if(curr == sub + 1) { //letters were swapped
            steps.insert(steps.begin(), {1, {a[i-1], b[j-1]}});
            j--;
            i--;
        }
        else if(curr == del + 1) { //letter was deleted from a
            steps.insert(steps.begin(), {2, {a[i-1], ' '}});
            i--;
        }
        else if(curr == ins + 1){ // letter from a was inserted into b
            steps.insert(steps.begin(), {3, {b[j-1], ' '}});
            j--;
        }
        else { // no operation was performed
            steps.insert(steps.begin(), {0, {' ', ' '}});
            j--;
            i--;
        }
    }

    cout << "Edit distance is: " << matrix[a.size()][b.size()] << endl <<endl;
    cout << "Using the steps: \n---------------------------------\n";
    stepPrinter(steps, a);
}



int main() {
    string word1;
    string word2;

    cout << "Enter word 1: ";
    cin >> word1;
    cout << "Enter word 2: ";
    cin >> word2;
    cout << endl;
    wagnerFischer(word1, word2);
    return 0;
}