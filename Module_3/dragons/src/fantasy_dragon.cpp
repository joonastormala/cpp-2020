#include "fantasy_dragon.hpp"

FantasyDragon::FantasyDragon(const std::string& name, size_t age, size_t size)
            : Dragon(name, age, size) {}

void FantasyDragon::Eat(std::list<Food>& f){
    for(std::list<Food>::iterator i = f.begin(); i != f.end();){
        if(i->type == PeopleFood || i->type == People) {
            std::cout << "Fantasy dragon ate: " << i->name << std::endl;
            size_++;
            i = f.erase(i);
        } else i++;
    }
}

void FantasyDragon::Hoard(std::list<Treasure>& t){
    for(std::list<Treasure>::iterator i = t.begin(); i != t.end();){
        if(i->type == Jewellery) {
            treasures_.push_back(*i);
            std::cout << "Fantasy dragon received: " << i->name << std::endl;
            i = t.erase(i);
        } else i++;
    }
}
