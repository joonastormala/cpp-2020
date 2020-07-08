#pragma once
#include "string_printer.hpp"
class DiagonalPrinter : public StringPrinter
{
public:
    DiagonalPrinter(std::string start = "", std::string end = "", std::ostream &out = std::cout)
        : StringPrinter(out), start_(start), end_(end) {}
    DiagonalPrinter *Clone() const
    {
        return new DiagonalPrinter(start_, end_, os_);
    }
    virtual StringPrinter &operator()(const std::string &arg)
    {
        int size = arg.size();
        if (start_.size() > 0)
            os_ << start_ << std::endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                os_ << " ";
            }
            os_ << arg[i];
            for (int j = 0; j < size - i - 1; j++)
            {
                os_ << " ";
            }
            os_ << std::endl;
        }
        if (end_.size() > 0)
            os_ << end_ << std::endl;
        return *this;
    }

private:
    std::string start_;
    std::string end_;
};
/* TODO: class DiagonalPrinter
 * ------------
 * Description:
 * A class that is used to print strings diagonally (see below).
 * The class inherits (public inheritance) class StringPrinter.
 * ------------
 * Functions:
 * 
 * A constructor that takes three parameters:
 *  - The first line, which is "" by default, i.e. it is not printed at all
 *  - The last line, which is "" by default, i.e. it is not printed at all either
 *  - A reference to the output stream, which is std::cout by default
 * 
 * Overrides the necessary members from the base class.
 * ------------
 * Other:
 * DiagonalPrinter prints a string diagonally. For the string "like this":
<first line>\n
l        \n
 i       \n
  k      \n
   e     \n
         \n
     t   \n
      h  \n
       i \n
        s\n
<last line>\n
 * where <first line> and <last line> are replaced by the strings given in the
 * constructor. If the first line is empty, it is not printed. The same applies
 * to the last line.
 */
