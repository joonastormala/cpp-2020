#include "register.hpp"
//TODO: implement Register's members
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include "aircraft.hpp"
#include "boat.hpp"

Register::~Register()
{
    for (auto i : vehicles_)
    {
        delete i;
    }
}

void Register::Add(Vehicle *v)
{
    vehicles_.push_back(v);
}

void Register::Save(const std::string &filename) const
{

    std::ofstream os(filename);
    for (auto i : vehicles_)
    {
        i->Write(os);
    }
}
bool Register::ReadLine(std::istream &stream)
{
    char temp = stream.peek();

    if (temp == 'A')
    {
        Aircraft *ret = Aircraft::Read(stream);
        vehicles_.push_back(ret);
        return true;
    }
    else if (temp == 'B')
    {
        Boat *ret = Boat::Read(stream);
        vehicles_.push_back(ret);
        return true;
    }
    else
    {
        std::string placeh;
        getline(stream, placeh);
        return false;
    }
}

int Register::Load(const std::string &filename)
{
    std::ifstream istr(filename);
    if (istr.rdstate() & (istr.failbit | istr.badbit))
    {
        return -1;
    }
    else
    {
        int counter = 0;
        while (!istr.eof())
        {
            ReadLine(istr) ? counter++ : counter;
        }
        return counter;
    }
}
void Register::Print()
{
    for (auto i : vehicles_)
    {
        i->Print();
    }
}
size_t Register::Size() const
{
    size_t ret = vehicles_.size();
    return ret;
}