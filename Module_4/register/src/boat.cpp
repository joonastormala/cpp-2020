#include "boat.hpp"
//TODO: implement Boat's members

Boat::Boat(std::string register_number, std::string owner, std::string name, double draft, double power)
    : Vehicle(register_number, owner), name_(name), draft_(draft), power_(power) {}

void Boat::Write(std::ostream &stream)
{
    stream << "B;" << GetRegisterNumber()
           << ";" << GetOwner()
           << ";" << name_
           << ";" << draft_
           << ";" << power_ << std::endl;
}

void Boat::Print()
{
    this->Write(std::cout);
}

Boat *Boat::Read(std::istream &stream)
{
    std::string temp;
    Boat *ret;
    std::getline(stream, temp, ';');
    if (temp != "B")
    {
        return NULL;
    }
    else
    {
        std::string reg, own, nam, dra, pow;
        std::getline(stream, reg, ';');
        std::getline(stream, own, ';');
        std::getline(stream, nam, ';');
        std::getline(stream, dra, ';');
        std::getline(stream, pow, '\n');
        ret = new Boat(reg, own, nam, stod(dra), stod(pow));
        return ret;
    }
}