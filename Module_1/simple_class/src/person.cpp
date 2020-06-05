#include "person.hpp"

Person::Person(const std::string& name, const int& yob)
    : name_(name), yob_(yob) {
}
int Person::GetAge(int year) const {
    return year - yob_;
}
std::string Person::GetName() const {
    return name_;
}

