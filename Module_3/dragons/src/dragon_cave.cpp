#include "dragon_cave.hpp"

DragonCave::DragonCave() {}
DragonCave::~DragonCave()
{
    for (auto i : dragons_)
        delete i;
}

const std::list<Dragon *> &DragonCave::GetDragons() const
{
    return dragons_;
}

void DragonCave::Accommodate(Dragon *d)
{
    dragons_.push_back(d);
}

void DragonCave::Evict(const std::string &n)
{
    // for(std::list<Dragon*>::iterator i = dragons_.begin(); i!=dragons_.end();i++){
    std::list<Dragon *>::iterator i = dragons_.begin();
    while (i != dragons_.end())
    {
        if (((*i)->GetName()).compare(n) == 0)
        {
            dragons_.erase(i);
            break;
        }
        i++;
    }
}

std::ostream &operator<<(std::ostream &os, const DragonCave &d)
{
    os << "DragonCave dwellers:\n";
    for (auto i : d.GetDragons())
    {
        os << std::endl;
        os << *i;
    }
    return os;
}