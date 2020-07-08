#include "printers.hpp"
#include "string_printer.hpp"
#include "standard_printer.hpp"
#include "diagonal_printer.hpp"
#include <list>
#include <exception>

void Printers::Add(const std::string &name, StringPrinter *printer)
{
    if (printer == nullptr)
    {
        throw std::invalid_argument("Invalid printer");
    }
    for (auto it = printers_.begin(); it != printers_.end(); it++)
    {
        if (it->first == name)
        {
            throw std::invalid_argument("Duplicate index");
            return;
        }
    }
    printers_[name] = printer;
}
