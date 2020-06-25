#include "aviary.hpp"

void Aviary::SpeakAll(std::ostream& os) const{
    for(auto i: aviary_){
        i->Speak(os);
    }
}

size_t Aviary::Size() const{
    return aviary_.size();
}

Bird* Aviary::operator[](size_t i){
    std::list<Bird*>::iterator it = aviary_.begin();
    for(size_t j = 0; j < i; j++, it++);
    return *it;
}

const Bird* Aviary::operator[](size_t i) const{
    std::list<Bird*>::const_iterator it = aviary_.begin();
    for(size_t j = 0; j < i; j++, it++);
    return *it;
}

Aviary::~Aviary(){
    for(auto i: aviary_){
        delete i;
    }
}