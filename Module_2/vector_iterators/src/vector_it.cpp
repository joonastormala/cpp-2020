#include <iostream>
#include <vector>
#include "vector_it.hpp"

using namespace std;

vector<int> ReadVector(){
    vector<int> v;
    int input;
    cin >> input;
    do {
        v.push_back(input);
    } while(cin >> input);
    return v;
}

void PrintSum1(const vector<int>&v){
    for(unsigned int i = 0; i<v.size()-1; i++){
        cout << (v[i] + v[i+1]) << " ";
    }
    cout << endl;
}

void PrintSum2(const vector<int>&v){
    unsigned int j = v.size() - 1;
    for(unsigned int i = 0; i<v.size()/2;i++,j--){
            cout << v[i]+v[j] << " ";
    }
    cout << endl;
}