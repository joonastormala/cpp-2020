#include "magic_dragon.hpp"

MagicDragon::MagicDragon(const std::string& name, size_t age, size_t size)
            : Dragon(name, age, size) {}

void MagicDragon::Eat(std::list<Food>& f){
    for(std::list<Food>::iterator i = f.begin(); i != f.end();){
        if(i->type == Herbs) {
            size_++;
            std::cout << "Magic dragon ate: " << i->name << std::endl;
            i = f.erase(i);
        } else i++;
    }
}

void MagicDragon::Hoard(std::list<Treasure>& t){
    for(std::list<Treasure>::iterator i = t.begin(); i != t.end();){
        if(i->type == Potions) {
            treasures_.push_back(*i);
            std::cout << "Magic dragon recieved: " << i->name << std::endl;
            i = t.erase(i);
        } else i++;
    }
    // std::list<Treasure>::iterator i = t.begin();
    // while(i != t.end()){
    //     if(i->type == Potions) {
    //         treasures_.push_back(*i);
    //         std::cout << "Magic dragon recieved: " << i->name << std::endl;
    //         i = t.erase(i);
    //     } else i++;
    // }
}
