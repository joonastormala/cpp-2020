#pragma once
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <map>
#include "standard_printer.hpp"
#include "diagonal_printer.hpp"
#include "string_printer.hpp"

class Printers
{
public:
    Printers() {}
    Printers(const Printers &printers)
    {
        *this = printers;
    }
    ~Printers()
    {
        for (auto it = printers_.begin(); it != printers_.end(); it++)
        {
            delete it->second;
        }
        printers_.clear();
    }
    StringPrinter &operator[](std::string name)
    {
        for (auto it = printers_.begin(); it != printers_.end(); it++)
        {
            if (name == it->first)
                return *(it->second);
        }
        throw std::invalid_argument("Unknown index");
    }
    Printers &operator=(const Printers &printers)
    {
        this->~Printers();
        for (auto it = printers.printers_.begin(); it != printers.printers_.end(); it++)
        {
            printers_[it->first] = it->second->Clone();
        }
        return *this;
    }

    void Add(const std::string &name, StringPrinter *printer);

private:
    std::map<std::string, StringPrinter *> printers_;
};
/* TODO: class Printers
 * ------------
 * Description:
 * A storage for StringPrinter pointers associated with a name. The class has 
 * ownership of the objects.
 * ------------
 * Functions:
 * 
 * A default constructor that initializes the object with zero printers.
 * 
 * A copy constructor that copies the object.
 * 
 * Add: A function that adds a new StringPrinter object to the collection
 * and associates it with a name.
 * Takes two parameters:
 *  - a string that contains the name
 *  - the StringPrinter pointer to be added
 * Throws:
 *  - std::invalid_argument if an association for the name already exists ("Duplicate index").
 *  - std::invalid_argument if the pointer is null ("Invalid printer").
 * Note: The Printers object takes ownership of the pointer and is
 *  therefore responsible for eventually calling delete on the pointer.
 * 
 * Indexing operator: The collection is indexed using the
 * name (string) and returns a reference to the associated StringPrinter.
 * Throws:
 *  - std::invalid_argument if an association does not exist ("Unknown index").
 * 
 * Copy assignment operator: copies the object given to self.
 * ------------
 * Members:
 * Whatever you deem necessary.
 * ------------
 * Other:
 * Copying means copying the contained StringPrinters as well.
 * Remember to also implement the destructor.
 */
