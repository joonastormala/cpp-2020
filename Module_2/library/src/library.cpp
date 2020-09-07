#include <iostream>
#include "book.hpp"
#include "customer.hpp"
#include "library.hpp"

Library::Library(const std::string &name) : name_(name), books_(), customers_() {}

std::string Library::GetName() const
{
    return name_;
}

std::vector<Book> &Library::GetBooks()
{
    return books_;
}

std::vector<Customer> &Library::GetCustomers()
{
    return customers_;
}

Book Library::FindBookByName(const std::string &name)
{
    for (auto i : books_)
    {
        if (i.GetName() == name)
        {
            return i;
        }
    }
    return Book("", "", "");
}

std::vector<Book> Library::FindBooksByAuthor(const std::string &author)
{
    std::vector<Book> b;
    for (auto i : books_)
    {
        if (i.GetAuthor() == author)
        {
            b.push_back(i);
        }
    }
    return b;
}

std::vector<Book> Library::FindAllLoanedBooks()
{
    std::vector<Book> l;
    for (auto i : customers_)
        for (int j = 0; j < i.GetLoanAmount(); j++)
        {
            l.push_back(i.GetLoans()[j]);
        }
    return l;
}

Customer Library::FindCustomer(const std::string &customer_id)
{
    for (auto i : customers_)
    {
        if (i.GetID() == customer_id)
        {
            return i;
        }
    }
    return Customer("", "");
}
