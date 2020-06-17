#include "customer.hpp"

#include <iostream>
#include <string.h>
#include <vector>
#include <limits>

Customer::Customer(const std::string& name, const std::string& id):
    name_(name), customer_id_(id), loaned_books_(){}

std::string Customer::GetName() const{
 return name_;
}

std::string Customer::GetID() const{
    return customer_id_;
}

int Customer::GetLoanAmount() const{
    return (int)loaned_books_.size();
}

std::vector<Book> Customer::GetLoans() const{
    return loaned_books_;
}

bool Customer::LoanBook(Book &b){
    if(b.Loan()){
        loaned_books_.push_back(b);
        return true;
    } else return false;
}

void Customer::ReturnBook(Book &b){
    int c = 0;
    for(std::vector<Book>::iterator i = loaned_books_.begin(); i != loaned_books_.end(); i++){
        if(loaned_books_[c].GetName() == b.GetName()){
            loaned_books_.erase(i);
            b.Restore();
            return;
        }
        c++;
    }
    //Test if nothing was found
    std::cout << "Book was not found" << std::endl;
}

void Customer::Print() const{
    std::cout   <<"Customer: " << name_ << ", " << customer_id_ << ", has "
                << loaned_books_.size() << " books on loan:"
                << std::endl;
    for(auto i : loaned_books_){
        std::cout << "- Book: " << i.GetName()
                  << ", author: " << i.GetAuthor()
                  << ", ISBN: " << i.GetISBN()
                  << ", loaned " << (i.GetStatus() ? "true" : "false")
                  << ", due date: " << i.GetDueDate().day << "."
                                  << i.GetDueDate().month << "."
                                  << i.GetDueDate().year
                  << std::endl;
    }
}