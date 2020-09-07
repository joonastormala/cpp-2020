#include "vector_strings.hpp"

#include <iostream>
#include <vector>

using namespace std;

void Adder(std::vector<std::string> &names)
{
    string tbaname;
    cout << "Enter a name:" << endl;
    cin >> tbaname;
    names.push_back(tbaname);
    cout << "Number of names in the vector:" << endl
         << names.size() << endl;
}

void Remover(std::vector<std::string> &names)
{
    cout << "Removing the last element:" << endl
         << names[names.size() - 1] << endl;
    names.pop_back();
}

void Printer(std::vector<std::string> &names)
{
    for (unsigned int i = 0; i < names.size(); i++)
    {
        cout << names[i] << endl;
    }
}

void CMDReader()
{
    string command;
    vector<string> names;
    cout << "Commands: ADD, PRINT, REMOVE, QUIT" << endl;
    while (command != "QUIT")
    {
        cout << "Enter a command:" << endl;
        cin >> command;
        if (command == "ADD")
        {
            Adder(names);
        }
        if (command == "PRINT")
        {
            Printer(names);
        }
        if (command == "REMOVE")
        {
            Remover(names);
        }
        // cout << command << endl;
    }
}
