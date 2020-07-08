#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "string_printer.hpp"
#include <sstream>
#include <stdexcept>
#include <iterator>
class StandardPrinter : public StringPrinter
{
public:
    StandardPrinter(std::ostream &out = std::cout)
        : StringPrinter(out) {}
    StandardPrinter *Clone() const
    {
        return new StandardPrinter(os_);
    }
    virtual StringPrinter &operator()(const std::string &arg)
    {
        os_ << arg << std::endl;
        return *this;
    }
};
/* TODO: class StandardPrinter
 * ------------
 * Description:
 * A minimal StringPrinter implementation with no special functionality.
 * ------------
 * Functions:
 * A constructor that takes a single parameter:
 *  - A reference to the output stream, which is std::cout by default
 * 
 * Overrides the necessary members from the base class.
 * ------------
 * Other:
 * StandardPrinter prints a string like one normally would but with a 
 * newline at the end. For the string "like this":
like this\n
*/
