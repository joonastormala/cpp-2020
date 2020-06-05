#ifndef AALTO_ELEC_CPP_PERSON
#define AALTO_ELEC_CPP_PERSON
#include <string>

class Person {
    public:
        Person(const std::string& name, const int& yob);
        std::string GetName() const;
        int GetAge(int year) const;
    private:
        std::string name_;
        int yob_;
};



#endif