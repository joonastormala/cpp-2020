#include "dog_class.hpp"

//Definitions of class functions with some errors


Dog(int a, string n) { 
    age_ = a; 
    name_ = n; 
}


Dog::setAge(int a) {
    age_ = a; 
}


Dog::GetAge() {
    return age_; 
}


Dog::SetName(string n) {
    name_ = n; 
}


Dog::getName() {
    return name_; 
}


