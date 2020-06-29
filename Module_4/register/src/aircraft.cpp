#include "aircraft.hpp"

Aircraft::Aircraft(std::string register_number, std::string owner, std::string model, double wingspan, unsigned int cruise_speed)
    : Vehicle(register_number, owner), model_(model), wingspan_(wingspan), cruise_speed_(cruise_speed) {}

void Aircraft::Write(std::ostream &stream)
{
    stream << "A;" << GetRegisterNumber()
           << ";" << GetOwner()
           << ";" << model_
           << ";" << wingspan_
           << ";" << cruise_speed_ << std::endl;
}

void Aircraft::Print()
{
    this->Write(std::cout);
}

Aircraft *Aircraft::Read(std::istream &stream)
{
    std::string temp;
    Aircraft *ret;
    std::getline(stream, temp, ';');
    if (temp != "A")
    {
        return NULL;
    }
    else
    {
        std::string reg, own, mod, wpn, spd;
        std::getline(stream, reg, ';');
        std::getline(stream, own, ';');
        std::getline(stream, mod, ';');
        std::getline(stream, wpn, ';');
        std::getline(stream, spd, '\n');
        ret = new Aircraft(reg, own, mod, stod(wpn), stoul(spd));
        return ret;
    }
}
