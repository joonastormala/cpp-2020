#include "dragon.hpp"

Dragon::Dragon(const std::string &name, size_t age, size_t size)
    : name_(name), age_(age), size_(size), treasures_() {}

std::ostream &operator<<(std::ostream &os, const Dragon &d)
{
    os << "Dragon named: " << d.GetName()
       << ", age: " << d.GetAge()
       << ", size: " << d.GetSize() << "\n"
       << "Treasures:\n";
    for (auto i : d.GetTreasures())
    {
        os << i.name << std::endl;
    }
    return os;
}