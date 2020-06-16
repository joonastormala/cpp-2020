#include "list.hpp"
#include <iostream>

using namespace std;

istream& GetLines(istream& is, list<string>& list){
    string str;
    while(getline(is, str)){
        if(str.size()>0) list.push_back(str);
    }
    return is;
}

void Print(const list<string>& list){
    for(auto i : list){
        cout << i << endl;
    }
}

void SortAndUnique(list<string>& list){
    list.unique();
    list.sort();
}
